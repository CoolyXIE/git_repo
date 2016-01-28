def singleNumber(nums):
    def findNextIndex(index):
        i = (index + 1)%len(nums)
        while nums[i] == None:
            i = (index + 1)%len(nums)
        return i 
    
    i = 0
    while(True):
        j = findNextIndex(i);
        print i, j, nums
        if i == j:
            return i
        if nums[i] == nums[j]:
            nums[i] = None
            nums[j] = None
            i = findNextIndex(j)
        else:
            i = j


nums = [1,2,3,3,1,2,4,5,4]
print singleNumber(nums)
    
    
            
    
                
