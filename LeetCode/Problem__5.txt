//Problema 1512 -- Leetcode
int numIdenticalPairs(int* nums, int numsSize){
int aux=0;
    for(int i = 0; i < numsSize; i++){
        for(int j = i+1; j < numsSize; j++){
            if(nums[i] == nums[j] && i < j){
                aux++;
            }
        }
    }
    return aux;
}
