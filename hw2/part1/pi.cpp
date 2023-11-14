#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <random>
#include <vector>
//#include <immintrin.h>

//#define VECTOR_SIZE 4

uint tosses_leftover;
uint64_t tosses_per_thread;
uint64_t in_circle = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* monteCarloPi(void* arg) {
    uint thread_id = static_cast<uint>(reinterpret_cast<std::uintptr_t>(arg));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    uint64_t local_in_circle = 0;

    uint64_t N;
    if(thread_id < tosses_leftover) {
        N = tosses_per_thread + 1;
    } else {
        N = tosses_per_thread;
    }

    //__m256d x_vec, y_vec, sum_vec;
    //double tmp[VECTOR_SIZE];    
    for (uint64_t i = 0; i < N; i += 1/*VECTOR_SIZE*/) {
        //for(int j = 0; j < VECTOR_SIZE; j++) {
        //    tmp[j] = dis(gen);
        //}
        //x_vec = _mm256_loadu_pd(tmp);
        //for(int j = 0; j < VECTOR_SIZE; j++) {
        //    tmp[j] = dis(gen);
        //}
        //y_vec = _mm256_loadu_pd(tmp);
        //sum_vec = _mm256_add_pd(_mm256_mul_pd(x_vec, x_vec), _mm256_mul_pd(y_vec, y_vec));
        //_mm256_storeu_pd(tmp, sum_vec); 
        //for(int j = 0; j < VECTOR_SIZE; j++) {
        //    if (tmp[j] <= 1.0) {
        //        local_in_circle++;
        //    }
        //}
        double x = dis(gen);
        double y = dis(gen);
        if (x * x + y * y <= 1.0) {
            local_in_circle++;
        }
    }

    pthread_mutex_lock(&mutex);
    in_circle += local_in_circle;
    pthread_mutex_unlock(&mutex);

    return nullptr;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <num_threads> <num_tosses>\n";
        return 1;
    }

    uint num_threads = std::stoi(argv[1]);
    uint64_t num_tosses = std::stoll(argv[2]);

    tosses_per_thread = num_tosses / num_threads;
    tosses_leftover = num_tosses % num_threads;

    std::vector<pthread_t> threads(num_threads - 1);
    
    uint i;
    for (i = 0; i < num_threads - 1; i++) {
        pthread_create(&threads[i], nullptr, monteCarloPi, reinterpret_cast<void*>(static_cast<std::uintptr_t>(i)));
    }

    monteCarloPi(reinterpret_cast<void*>(static_cast<std::uintptr_t>(i)));

    for (uint i = 0; i < num_threads - 1; i++) {
        pthread_join(threads[i], nullptr);
    }

    double pi_estimate = 4.0 * in_circle / num_tosses;

    std::cout.precision(8);

    std::cout << pi_estimate << std::endl;

    return 0;
}
