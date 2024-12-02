resoluçao em C

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int i=0;
    while(i<numsSize-1){
        int j=i+1;
        while(j<numsSize){
            if(nums[i]+nums[j]==target){
                int*result=(int*)malloc(2*sizeof(int));
                result[0]=i;
                result[1]=j;
                *returnSize=2;
                return result;
            }
            j++;
        }
        i++;
    }
    *returnSize=0;
    return NULL;
}

