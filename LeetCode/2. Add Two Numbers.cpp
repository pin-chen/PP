//2. Add Two Numbers
//hint: big number add
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int sum = l1->val + l2->val;
        ListNode *ans = new ListNode( sum % 10);
        ListNode *now = ans;
        sum /= 10;
        l2 = l2 -> next; 
        l1 = l1 -> next;
        while(l1 || l2){
            if(l2){
                sum += l2->val;
                l2 = l2 -> next;    
            }
            if(l1){
                sum += l1->val;
                l1 = l1 -> next;
            }
            now->next = new ListNode(sum % 10);
            sum /= 10;
            now = now->next;
        }
        if(sum) now->next = new ListNode(sum);
        return ans;
    }
};
