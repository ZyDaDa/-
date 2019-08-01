#include <iostream>

using namespace std; 


/**
	ֱ�Ӳ�������
ʱ�临�Ӷȣ�O(n^2)
�ռ临�Ӷȣ�O(1) 
*/
void InsertSort(int R[], int n){
	int i, j;
	int temp;
	for(i=1; i<n; ++i){	//��һ��Ԫ�ز��ñȽ� �ӵڶ�����ʼ���� 
		temp = R[i];	//��������Ԫ���ݴ� 
		j = i-1;		//�ҵ�������Ԫ��ǰһ��Ԫ�� 
		while(j>=0 && temp<R[j]){	//ѭ��Ѱ�Ҳ���λ��	��δ�ҵ�����ѭ���� 
			R[j+1] = R[j];	//�����Ƚ�Ԫ�غ��� 
			--j;	
		}
		R[j+1] = temp;	//�ҵ�����λ�� ����Ԫ�� 
	}
} 

/**
	�۰��������
ʱ�临�Ӷȣ�O(n^2)
�ռ临�Ӷȣ�O(1) 
*/
void BinaryInsertSort(int R[], int n){
	int low, high, m;	
	int i, j, temp;
	for(i=1; i<n; ++i){	//�ӵڶ���Ԫ�ؿ�ʼ���� 
		low = 0;
		high = i-1;		
		temp = R[i];	//�������Ԫ�� 
		while(low <= high){	 
			m = (low + high)/2;
			if(R[m] > temp)
				high = m-1;
			else
				low = m+1;
		}
		for(j=i-1; j>high; --j)	//��high�����Ԫ��ȫ������һλ 
			R[j+1] = R[j];
		R[high+1] = temp;  		//����Ԫ�� 
	} 
}

/**
	ϣ������ 
ʱ�临�Ӷȣ�O(n^2)
�ռ临�Ӷȣ�O(1) 
*/
void ShellSort(int R[], int n){
	int i, j, temp, k; 
	int gap;	//gapΪ����	 
	for(gap=n/2; gap>0; gap/= 2){	//������ÿ������һ�� 
		//��gap��������ȫ���������� 
		for(i=0; i<gap; i++){
			//ֱ�Ӳ������� 
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
	ð������
ʱ�临�Ӷȣ�O(n^2)
�ռ临�Ӷȣ�O(1) 
*/
void BubbleSort(int R[], int n){
	int i, j, flag, temp;
	for(i=n-1; i>=1; --i){	//ʹ�±�Ϊ i ��Ԫ��ʼ��Ϊ���ֵ 
		flag = 0;			//��Ǳ��� �����Ƿ����˸ı� 
		for(j=1; j<=i; ++j){ 
			if(R[j-1] > R[j]){	//����Ԫ�� 
				temp = R[j];
				R[j] = R[j-1];
				R[j-1] = temp;
				flag = 1;		//flag==1 ֤�����˷����˽���  
			}
		}
		if(flag == 0)	//���δ�������������������� 
			return;
	}
} 

/**
	��������
ʱ�临�Ӷȣ�O(n*log2^n)
�ռ临�Ӷȣ�O(log2^n) 
*/
void QuickSort(int R[], int low, int high){
	int temp;
	int i=low, j=high;
	if(low < high){	
		temp = R[low];	//������ŦԪ�� 
		//ѭ����Ԫ�ط�Ϊ {С����Ŧ ��Ŧ ������Ŧ} 
		while(i<j){	
			while(j>i && R[j]>=temp) --j;	//��������ɨ���ҵ�С��temp��Ԫ�� 
			if(i<j){	//������ŦԪ����� 
				R[i] = R[j];
				++i;
			}
			while(i<j && R[i]<temp)	++i;	//��������ɨ���ҵ�����temp��Ԫ�ط����ұ� 
			if(i<j){
				R[j] = R[i];
				--j;
			}
		}
		R[i] = temp;	//��temp��������λ�� 
		QuickSort(R, low, i-1);	//�ݹ��С����Ŧ��Ԫ�ؽ������� 
		QuickSort(R, i+1, high);//�ݹ�Դ�����Ŧ��Ԫ�ؽ������� 
	}	
}

/**
	��ѡ������ 
ʱ�临�Ӷȣ�O(n^2)
�ռ临�Ӷȣ�O(1) 
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
	������ 
ʱ�临�Ӷȣ�O(n*log2^n)
�ռ临�Ӷȣ�O(1) 
*/
//�������� 
void sift(int R[], int low, int high){
	int i=low, j=2*i+1;	//j Ϊ i �����ӽ�� 
	int temp = R[i];	//����i��� 
	while(j <= high){
		if(j<high && R[j]<R[j+1])	//�� j ָ�� i �������������� 
			++j;
		if(temp < R[j]){	//���iС�ں��ӽ�� �򽻻���㣬 ��ָ�򱻽����Ľ����亢�ӽ�� 
			R[i] = R[j];
			i = j;
			j = 2*i +1;
		}
		else	//����˳�� ���� 
			break;
	}
	R[i] = temp;	//����������������λ�� 
}
//�������� 
void heapSort(int R[], int n){
	int i;
	int temp;
	for(i=n/2-1; i>0; --i)	//������ʼ�󶥶� 
		sift(R, i, n-1);
	for(i=n-1; i>0; --i){	//����ѭ������ɶ����� 
		temp = R[0];
		R[0] = R[i];
		R[i] = temp;
		sift(R, 0, i-1);
	}
}

/**
	��·�鲢���� 
ʱ�临�Ӷȣ�O(n*log2^n)
�ռ临�Ӷȣ�O(n) 
*/
//�鲢���� 
void merge(int arr[], int low, int mid, int high){
	int i, j, k;
	int n1 = mid - low + 1;	//����ǰ��γ��� 
	int n2 = high - mid;	//������γ��� 
	int L[n1], R[n2];		//��ʼ���������� 
	for(i=0; i<n1; i++)
		L[i] = arr[low+i];
	for(j=0; j<n2; j++)
		R[j] = arr[mid + 1 + j];

	i = 0;
	j = 0;
	k = low;
	while(i<n1 && j<n2){	//�����ι鲢��һ�� 
		if(L[i] <= R[j])
			arr[k] = L[i++];
		else
			arr[k] = R[j++];
		k++;
	}
	while(i < n1)		//��ʣ��Ԫ�ز��� 
		arr[k++] = L[i++];
	while(j < n2)
		arr[k++] = R[j++];
}
//�鲢���� 
void mergeSort(int arr[], int low, int high){
	if(low < high){
		int mid = (low + high)/2;
		mergeSort(arr, low, mid);	//�鲢ǰ��� 
		mergeSort(arr, mid+1, high);//�鲢���� 
		merge(arr, low, mid, high);	//��low - mid  ��  mid+1 - high1�����ι鲢Ϊһ�� 
	}
} 

/**
	��������
ʱ�临�Ӷȣ�O(n*log2^n)
�ռ临�Ӷȣ�O(n) 
*/
//��ȡ����Ԫ�����λ�� 
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
//�������� 
void radixSort(int R[], int n){
    int d = getMaxDigit(R, n);
    int tmp[n];
    int count[10]; //������
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++){	//����d������
        for(j = 0; j < 10; j++)
            count[j] = 0;	//ÿ�η���ǰ��ռ�����
        for(j = 0; j < n; j++){
            k = (R[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
        for(j = n - 1; j >= 0; j--){ //������Ͱ�м�¼�����ռ���tmp��
            k = (R[j] / radix) % 10;
            tmp[count[k] - 1] = R[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //����ʱ��������ݸ��Ƶ�R��
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
