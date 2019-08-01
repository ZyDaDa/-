#include <iostream>

using namespace std; 


/**
	直接插入排序
时间复杂度：O(n^2)
空间复杂度：O(1) 
*/
void InsertSort(int R[], int n){
	int i, j;
	int temp;
	for(i=1; i<n; ++i){	//第一个元素不用比较 从第二个开始插入 
		temp = R[i];	//将待插入元素暂存 
		j = i-1;		//找到待插入元素前一个元素 
		while(j>=0 && temp<R[j]){	//循环寻找插入位置	若未找到进入循环体 
			R[j+1] = R[j];	//将被比较元素后移 
			--j;	
		}
		R[j+1] = temp;	//找到插入位置 插入元素 
	}
} 

/**
	折半插入排序
时间复杂度：O(n^2)
空间复杂度：O(1) 
*/
void BinaryInsertSort(int R[], int n){
	int low, high, m;	
	int i, j, temp;
	for(i=1; i<n; ++i){	//从第二个元素开始插入 
		low = 0;
		high = i-1;		
		temp = R[i];	//保存插入元素 
		while(low <= high){	 
			m = (low + high)/2;
			if(R[m] > temp)
				high = m-1;
			else
				low = m+1;
		}
		for(j=i-1; j>high; --j)	//将high后面的元素全部后移一位 
			R[j+1] = R[j];
		R[high+1] = temp;  		//插入元素 
	} 
}

/**
	希尔排序 
时间复杂度：O(n^2)
空间复杂度：O(1) 
*/
void ShellSort(int R[], int n){
	int i, j, temp, k; 
	int gap;	//gap为步长	 
	for(gap=n/2; gap>0; gap/= 2){	//将步长每次缩短一半 
		//对gap个子序列全部进行排序 
		for(i=0; i<gap; i++){
			//直接插入排序 
			for( j = i+gap; j<n; j=j+gap){
				if(R[j]<R[j-gap]){
					temp = R[j];
					k = j-gap;
					while(k>=0 && R[k]>temp){
						R[k+gap] = R[k];
						k -= gap;
					}
					R[k+gap] = temp;
				}
			}
		}
	}
}

/**
	冒泡排序
时间复杂度：O(n^2)
空间复杂度：O(1) 
*/
void BubbleSort(int R[], int n){
	int i, j, flag, temp;
	for(i=n-1; i>=1; --i){	//使下标为 i 的元素始终为最大值 
		flag = 0;			//标记变量 该趟是否发生了改变 
		for(j=1; j<=i; ++j){ 
			if(R[j-1] > R[j]){	//交换元素 
				temp = R[j];
				R[j] = R[j-1];
				R[j-1] = temp;
				flag = 1;		//flag==1 证明该趟发生了交换  
			}
		}
		if(flag == 0)	//如果未发生交换代表序列有序 
			return;
	}
} 

/**
	快速排序
时间复杂度：O(n*log2^n)
空间复杂度：O(log2^n) 
*/
void QuickSort(int R[], int low, int high){
	int temp;
	int i=low, j=high;
	if(low < high){	
		temp = R[low];	//保存枢纽元素 
		//循环将元素分为 {小于枢纽 枢纽 大于枢纽} 
		while(i<j){	
			while(j>i && R[j]>=temp) --j;	//从左往右扫描找到小于temp的元素 
			if(i<j){	//放在枢纽元素左边 
				R[i] = R[j];
				++i;
			}
			while(i<j && R[i]<temp)	++i;	//从右往左扫描找到大于temp的元素放在右边 
			if(i<j){
				R[j] = R[i];
				--j;
			}
		}
		R[i] = temp;	//将temp放在最终位置 
		QuickSort(R, low, i-1);	//递归对小于枢纽的元素进行排序 
		QuickSort(R, i+1, high);//递归对大于枢纽的元素进行排序 
	}	
}

/**
	简单选择排序 
时间复杂度：O(n^2)
空间复杂度：O(1) 
*/
void SelectSort(int R[], int n){
	int i, j, k;
	int temp;
	for(i=0; i<n; ++i){
		k = i;
		for(j=i+1; j<n; ++j)
			if(R[k] > R[j])
				k = j;
		temp = R[i];
		R[i] = R[k];
		R[k] = temp;
	} 
} 

/**
	堆排序 
时间复杂度：O(n*log2^n)
空间复杂度：O(1) 
*/
//调整函数 
void sift(int R[], int low, int high){
	int i=low, j=2*i+1;	//j 为 i 的左孩子结点 
	int temp = R[i];	//保存i结点 
	while(j <= high){
		if(j<high && R[j]<R[j+1])	//将 j 指向 i 两个孩子中最大的 
			++j;
		if(temp < R[j]){	//如果i小于孩子结点 则交换结点， 并指向被交换的结点和其孩子结点 
			R[i] = R[j];
			i = j;
			j = 2*i +1;
		}
		else	//满足顺序 跳出 
			break;
	}
	R[i] = temp;	//被调整结点放入最终位置 
}
//堆排序函数 
void heapSort(int R[], int n){
	int i;
	int temp;
	for(i=n/2-1; i>0; --i)	//建立初始大顶堆 
		sift(R, i, n-1);
	for(i=n-1; i>0; --i){	//进行循环，完成堆排序 
		temp = R[0];
		R[0] = R[i];
		R[i] = temp;
		sift(R, 0, i-1);
	}
}

/**
	二路归并排序 
时间复杂度：O(n*log2^n)
空间复杂度：O(n) 
*/
//归并操作 
void merge(int arr[], int low, int mid, int high){
	int i, j, k;
	int n1 = mid - low + 1;	//计算前半段长度 
	int n2 = high - mid;	//计算后半段长度 
	int L[n1], R[n2];		//初始化两个数组 
	for(i=0; i<n1; i++)
		L[i] = arr[low+i];
	for(j=0; j<n2; j++)
		R[j] = arr[mid + 1 + j];

	i = 0;
	j = 0;
	k = low;
	while(i<n1 && j<n2){	//将两段归并成一段 
		if(L[i] <= R[j])
			arr[k] = L[i++];
		else
			arr[k] = R[j++];
		k++;
	}
	while(i < n1)		//将剩余元素并入 
		arr[k++] = L[i++];
	while(j < n2)
		arr[k++] = R[j++];
}
//归并排序 
void mergeSort(int arr[], int low, int high){
	if(low < high){
		int mid = (low + high)/2;
		mergeSort(arr, low, mid);	//归并前半段 
		mergeSort(arr, mid+1, high);//归并后半段 
		merge(arr, low, mid, high);	//将low - mid  和  mid+1 - high1的两段归并为一段 
	}
} 

/**
	基数排序
时间复杂度：O(n*log2^n)
空间复杂度：O(n) 
*/
//获取数组元素最大位数 
int getMaxDigit(int R[], int n)
{
	int digit = 1;
	int base = 10;
	for (int i=0; i<n; i++)
	{
		while (R[i] >= base)
		{
			++digit;
			base *= 10;
		}
	}
	return digit;
}
//基数排序 
void radixSort(int R[], int n){
    int d = getMaxDigit(R, n);
    int tmp[n];
    int count[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++){	//进行d次排序
        for(j = 0; j < 10; j++)
            count[j] = 0;	//每次分配前清空计数器
        for(j = 0; j < n; j++){
            k = (R[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = n - 1; j >= 0; j--){ //将所有桶中记录依次收集到tmp中
            k = (R[j] / radix) % 10;
            tmp[count[k] - 1] = R[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到R中
            R[j] = tmp[j];
        radix = radix * 10;
    }
}




int main(int argc, char** argv) {
	int a[10] = {146,5,61,27,8,44,5,16,46,78};
	radixSort(a,10);
	for(int i=0; i<10;++i)
		cout<<a[i]<<' '<<endl;
	
	return 0;
}
