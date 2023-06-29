#include <stdio.h>

//Satýrý saða doðru rotate eder.
void rotate(int arr[], int n);

//Satýrýn elemanlarýnýn üst satýrdaki elemanlarla çakýþýp çakýþmadýðýný kontrol eder.
int isValid(int **board, int N, int row);

// Bir satýr için tüm olasý sýralamalarý dener.
// Eðer bir çözüm bulunursa, çözümü yazdýrýr.
void backtrack(int **board, int N, int row, int *solutionFlag);

void printSolution(int **board , int N);

//bactrack fonksiyonuna daha fazla deðiþken gönderilmek istenmemiþ bu yüzden detay deðiþkeni global olarak tanýmlanmýþtýr.
int detay;//Detay modda çalýþtýrýldýðýnda 1 olur.

int main() {
	
	int N,mod;
	int **board;
	char colors[8][10]={ "Siyah", "Kirmizi", "Turuncu", "Sari", "Yesil", "Mavi", "Mor", "Beyaz"};
	int i,j;
	int solutionFlag = 0;
	
	do{
		printf("3 ile 8 arasinda N sayisi giriniz: ");
		scanf("%d",&N);
	}while(N>8 || N<3);
	
  	board = (int**)malloc(N*sizeof(int*));
  	for(i=0; i<N; i++){
    	board[i] = (int*)malloc(N*sizeof(int));
	}
	
	printf("\n");
	
	printf("0-Siyah\n1-Kirmizi\n2-Turuncu\n3-Sari\n4-Yesil\n5-Mavi\n6-Mor\n7-Beyaz\n\n");
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			
			do{
				
				printf("%d.Satir %d.Sutun degerini giriniz: ",i+1,j+1);
				scanf("%d",&board[i][j]);
				
			}while(board[i][j] > 7 || board[i][j] < 0);
			
		}
		printf("\n");
	}
	
	do{
		
		printf("Menu: \n1-Normal Modda Calistirma \n2-Detay Modda Calistirma \nMod Numarasini Giriniz :");
		scanf("%d",&mod);
		
	}while(mod != 1 && mod != 2);
	
	if(mod == 2){
		detay = 1;
	}
	
	printf("\n");
	
	if(detay == 1){
		printf("0. Satir -> ");
    	for(j=0 ; j<N ; j++)
    		printf("%d ",board[0][j]);
	}
	printf("\n");
	
	backtrack(board,  N, 1, &solutionFlag);
	printf("\n");
	
	if (solutionFlag == 0) {
			printf("Sonuc bulunamadi\n");
	}else{
		printf("Sonuc bulundu\n");
		printSolution(board,N);
	}
	
	printf("\n");
	
	int tmp;
	for (i = 0; i < N; i++) {
    	for (j = 0; j < N; j++) {
    		tmp = board[i][j];
    		printf("%8s ", colors[tmp]);
    	}
    	printf("\n");
  	}

return 0;
}

void backtrack(int **board, int N, int row, int *solutionFlag) {
	int i=0,j;

  	// Eðer tüm satýrlar için bir sýralama bulunduysa, çözüm bulundu demektir.
	if (row == N) {
    	(*solutionFlag)=1;
    	return;
	}

  	// Bu satýr için tüm olasý sýralamalarý dener.
	while (i<N && (*solutionFlag)!=1) {
		
    	// Eðer bu sýralama üst satýrlardaki renklerle çakýþmýyorsa,
    	// bir sonraki satýra geçer ve o satýr için tüm sýralamalarý denemeye devam eder.
    	if (isValid(board, N, row)) {
    		
    		if(detay == 1){
    			printf("%d. Satir uygun-> ",row);
    			for(j=0 ; j<N ; j++)
    				printf("%d ",board[row][j]);
    			printf("\n");
			}
    		
    		backtrack(board, N, row + 1, solutionFlag);
    		
    	}else if(detay == 1 && i != N){
    		
    		printf("%d. Satir uygun degil-> ",row);
    		for(j=0 ; j<N ; j++)
    			printf("%d ",board[row][j]);
    		printf("\trotate edilecek\n");
    		
		}
    	//Satýr uygun olabilir ama bir sonraki satýrlar uygun olmayabilir bu yüzden
    	//Rotate iþlemi çözüm bulunamadýðý zamanlarda devam etmeli
		if((*solutionFlag)!=1){
    		rotate(board[row], N);
		}
		i++;
  	}
  	
return;
}

void rotate(int arr[], int n) {
	int temp = arr[n - 1],i;

	for (i = n - 1; i > 0; i--) {
		arr[i] = arr[i - 1];
	}
	arr[0] = temp;
}

int isValid(int **board, int N, int row) {
	int i,j;
	
  	for (i = 0; i < row; i++) {
    	for (j = 0; j < N; j++) {
    		if (board[row][j] == board[i][j]) {
    			return 0;
    		}
    	}
	}
return 1;
}

void printSolution(int **board , int N) {
	int i,j;
	
	for (i = 0; i < N; i++) {
    	for (j = 0; j < N; j++) {
    		printf("%d ", board[i][j]);
    	}
    	printf("\n");
  	}
  	printf("\n");
}

