//load the library that use in application
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// stack untuk tumpukan pengembalian buku
struct stack{
  int count;
  struct data_stack *top;
  
};
typedef struct stack stack;

// linked list untuk menyimpan data stack/ tumpukan 
struct data_stack {
	char kode_buku[255];
    struct data_stack *next;
};
typedef struct data_stack data_stack;

// linked list untuk meyimpan data peminjam buku
struct peminjam {
    char npm[255];
    char nama[255];
    char prodi[255];
    char kode_buku[255];
    struct peminjam *next;
};
typedef struct peminjam peminjam;

// double linked list untuk menyimpan list buku
struct rak_buku {
    char nama_buku[255];
    char kode_buku[255];
    struct rak_buku *kiri;
    struct rak_buku *kanan;
};
typedef struct rak_buku rak_buku;

// struct array untuk deklarasi list buku awal yang nantinya akan di masukkan ke double linked list rak buku
struct buku {
    char nama_buku[255];
    char kode_buku[255];
};
typedef struct buku buku;


// stack function untuk membuat awal stack
stack createStack(void){
  stack head;
  head.count = 0;
  head.top = NULL;
  return head;
}

// register name function
// list fungsi
void bukaPerpus(rak_buku **head_buku, rak_buku **tail_buku, buku list_buku[3], peminjam **head);
void lihatRakBuku(rak_buku *head_buku);
void lihatPeminjam(peminjam *head);
void tambahPeminjam(peminjam **head_peminjam, rak_buku **head_buku, rak_buku **tail_buku);
int ambilBuku(rak_buku **head_buku, rak_buku **tail_buku, char target[255]);
void stackPush(stack *head_stack, char kode_buku[255]);
void stackPop(stack *head_stack);
void kembalikanBuku(stack *head_stack, peminjam **head_peminjam);
const char* hapusPeminjam(peminjam **head_peminjam, char target[255]);
void tambahBuku(rak_buku **head_buku, rak_buku **tail_buku, char nama_buku[255], char kode_buku[255]);
void lihatTumpukan(stack *head, rak_buku **head_buku, rak_buku **tail_buku,buku list_buku[3]);

//THE MAIN PROGRAM
int main()
{
 // deklarasi variable
  char selectMenu;
  stack head_stack;
  head_stack = createStack();
  rak_buku *head_buku, *tail_buku;
  peminjam *head_peminjam;
  head_peminjam = NULL;
  head_buku = NULL;
  tail_buku = NULL;
  // deklarasi list buku awal
  buku list_buku[3] = { 
    { "hoaks", "HK02J" }, 
    { "hoaks", "HK03J" }, 
    { "hoaks", "HK04J" } 
  };
  
  //loop the app menu with do-while
  do{
    
  system("cls");
    
  //app menu 
	printf(" ========== Perpustakaan ========== \n");
	printf("1. Buka Perpustakaan\n");
	printf("2. Lihat Daftar Buku\n");
	printf("3. Pinjam Buku\n");
	printf("4. Lihat Daftar Peminjam\n");
  printf("5. Kembalikan Buku\n");
  printf("6. Lihat Tumpukan Pengembalian Buku\n");
	printf("ENTER YOUR OPTION (PRESS 'q' FOR QUIT) : ");
	fflush(stdin);
	scanf("%c", &selectMenu);
    if (selectMenu == '1'){
		  bukaPerpus(&head_buku, &tail_buku, list_buku, &head_peminjam);
    }else if (selectMenu == '2'){
      lihatRakBuku(head_buku);
	    getch();
    }else if (selectMenu == '3')
		  tambahPeminjam(&head_peminjam, &head_buku, &tail_buku);
    else if (selectMenu == '4'){
      lihatPeminjam(head_peminjam);
      getch();
    }else if (selectMenu == '5')
		  kembalikanBuku(&head_stack, &head_peminjam);
    else if (selectMenu == '6')
        lihatTumpukan(&head_stack, &head_buku, &tail_buku, list_buku);
  } while (selectMenu != 'q');
  
}

void kembalikanBuku(stack *head_stack, peminjam **head_peminjam){
    char npm[255], kode_buku[255];
    if(*head_peminjam != NULL){
        lihatPeminjam(*head_peminjam);
        printf("\nMasukkan NPM\t: ");
        fflush(stdin);
        gets(npm);
        strcpy(kode_buku, hapusPeminjam(head_peminjam, npm));
        stackPush(head_stack, kode_buku);
        // printf("%s", hapusPeminjam(head_peminjam, npm));
        printf("Pengembalian Buku Berhasil..");
        getch();
    }else{
        system("cls");
        printf("Tidak Ada Peminjam");
        getch();
    }
    

}

const char* hapusPeminjam(peminjam **head_peminjam, char target[255]){
  peminjam *pCur, *pPre;
//   system("cls");
  pPre = NULL;
  pCur = *head_peminjam;
  //searching data target
  while (pCur != NULL && strcmp(pCur->npm, target) != 0) {
    pPre = pCur;
    pCur = pCur -> next;
  }

  if (pCur == NULL){
     return "0";
    // printf("\nDATA NOT FOUND !");
    //  getch();
  }
  else{
    if(pCur == *head_peminjam){
        *head_peminjam = pCur->next;
    }else{
        pPre->next = pCur->next;
    }
    free(pCur);
    return pCur->kode_buku;
  }
     
    //  return pCur->kode_buku;
    //  free(pCur);
}
//========================================================
void stackPush(stack *pHead, char kode_buku[255]){
  data_stack *pNew;
//   system("cls");
  if((*pHead).count < 3){
    
    pNew = (data_stack *)malloc(sizeof(data_stack));

    if (pNew != NULL){ 
      strcpy(pNew->kode_buku, kode_buku);
      pNew->next = pHead->top;
      (*pHead).top = pNew;
      (*pHead).count += 1;
    }
    else{
        printf("ERR: NOT ENOUGH MEMORY");
        getch();
    }
  }else{
    printf("Stack Penuh");
    getch();
  }
}

void stackPop(stack *head)
{
  data_stack *pCur;
  system("cls");
  pCur = (*head).top;
  if (pCur == NULL){
     printf("\nDATA NOT FOUND !");
     getch();
  }
  else{
    (*head).top = pCur->next;
    (*head).count -= 1;
     free(pCur);
  }

}
void tambahPeminjam(peminjam **pHead, rak_buku **head_buku, rak_buku **tail_buku){
  char data_npm[255];
  char data_nama[255], data_prodi[255], data_kode_buku[255];
  peminjam *pNew, *pCur = *pHead;
  system("cls");
  fflush(stdin);
  if (*head_buku != NULL){   
    lihatRakBuku(*head_buku);
    printf("\nMasukkan Kode Buku yang Dipinjam : ");
    fflush(stdin);
    gets(data_kode_buku);
    if(!(ambilBuku(head_buku, tail_buku, data_kode_buku))){
        printf("Masukkan NPM : ");
        fflush(stdin);
        gets(data_npm);
        printf("Masukkan Nama : ");
        fflush(stdin);
        gets(data_nama);
        printf("Masukkan Prodi : ");
        fflush(stdin);
        gets(data_prodi);

        pNew = (peminjam *)malloc(sizeof(peminjam));
        if (pNew != NULL){ 
                strcpy(pNew->npm, data_npm);
                strcpy(pNew->nama, data_nama);
                strcpy(pNew->prodi, data_prodi);
                strcpy(pNew->kode_buku, data_kode_buku);
        }
        else{
            printf("ERR: NOT ENOUGH MEMORY");
            getch();
        }
        // special case for the empty list
        if (pCur == NULL){
            //add peminjam to linked list
            pNew->next = *pHead;
            *pHead = pNew;
        }else{
            //search data
            while (pCur -> next != NULL) {
                    pCur = pCur -> next;
            }
            pNew->next = pCur->next;
            pCur->next = pNew;
        }
        printf("Peminjaman Berhasil...");
        getch();
    }else{
       printf("Buku dengan kode %s tidak ada", data_kode_buku);
       getch(); 
    }   
  }else{
    printf("Perpustakkan Belum Buka / Buku Habis");
    getch();
  }
}

void bukaPerpus(rak_buku **phead_buku, rak_buku ** ptail_buku, struct buku list_buku[3], peminjam **head_peminjam){
    rak_buku *bukuBaru;
  system("cls");
    if(*phead_buku != NULL || *head_peminjam != NULL){  
      printf("Perpustakaan Sudah Buka..");
      getch();
    }else{
      for(int i = 0; i < 3; i++){
          bukuBaru = (rak_buku *)malloc(sizeof(rak_buku));
          if (bukuBaru != NULL){
              strcpy(bukuBaru->nama_buku, list_buku[i].nama_buku);
              strcpy(bukuBaru->kode_buku, list_buku[i].kode_buku);
              if (*phead_buku == NULL){
              bukuBaru->kiri = NULL;
              bukuBaru->kanan = *phead_buku;
              *phead_buku = bukuBaru;
              *ptail_buku = bukuBaru;
              }
              else{
              bukuBaru->kiri = *ptail_buku;
              bukuBaru->kiri->kanan = bukuBaru;
              bukuBaru->kanan = NULL;
              *ptail_buku = bukuBaru;
              }
                  
          }
          else{
              printf("ERR: NOT ENOUGH MEMORY");
              getch();
          }
      }
      printf("Perpustakaan Telah Dibuka..\nBuku Berhasil Ditambahkan...");
      getch();
    }
}

void tambahBuku(rak_buku **phead_buku, rak_buku ** ptail_buku, char nama_buku[255], char kode_buku[255]){
  rak_buku *bukuBaru;
  system("cls");
    bukuBaru = (rak_buku *)malloc(sizeof(rak_buku));
    if (bukuBaru != NULL){
        strcpy(bukuBaru->nama_buku, nama_buku);
        strcpy(bukuBaru->kode_buku, kode_buku);
        if (*phead_buku == NULL){
        bukuBaru->kiri = NULL;
        bukuBaru->kanan = *phead_buku;
        *phead_buku = bukuBaru;
        *ptail_buku = bukuBaru;
        }
        else{
        bukuBaru->kiri = *ptail_buku;
        bukuBaru->kiri->kanan = bukuBaru;
        bukuBaru->kanan = NULL;
        *ptail_buku = bukuBaru;
        }
            
    }
    else{
        printf("ERR: NOT ENOUGH MEMORY");
        getch();
    }
  
}

int ambilBuku(rak_buku **head_buku, rak_buku **tail_buku, char target[255])
{
  rak_buku *pCur, *pPre;
  system("cls");
  pPre = NULL;
  pCur = *head_buku;
  
  while (pCur != NULL && strcmp(pCur->kode_buku, target) != 0) { 
    pPre = pCur;
    pCur = pCur -> kanan;
  }

  if (pCur == NULL){
     return 1;
  } else{
    if (pCur == *head_buku){
      pCur->kanan->kiri = NULL;
      *head_buku = pCur->kanan;
    }else if(pCur == *tail_buku){
      pCur->kiri->kanan = NULL;
      *tail_buku = pCur->kiri;
    }else{
     pPre->kanan = pCur->kanan;
     pPre->kanan->kiri = pPre;
    }
    free(pCur);
    return 0;
  } 
}

void lihatRakBuku(rak_buku *head_buku){
	rak_buku *pWalker, *tes;
    if (head_buku != NULL){
        system("cls");
        pWalker = head_buku;
        printf("\n==== Daftar Buku / Rak Buku ====");
        while (pWalker != NULL){
            printf("\n-----------------------------------------");
            printf("\nNama Buku\t: %s \nKode Buku\t: %s", pWalker -> nama_buku, pWalker -> kode_buku);
            printf("\n-----------------------------------------");
            pWalker = pWalker -> kanan;
        }
    }else{
        system("cls");
        printf("Perpustakkan Belum Buka / Buku Habis");
    }
}

void lihatPeminjam(peminjam *head){
    if (head != NULL){
        peminjam *pWalker;
        system("cls");
        pWalker = head;
        printf("==== List Peminjam Buku ====");
        while (pWalker != NULL){
            printf("\n-----------------------------------------");
            printf("\nNPM\t: %s \nNama\t: %s \nProdi\t: %s \nKode Buku yang dipinjam : %s", pWalker -> npm, pWalker -> nama, pWalker -> prodi, pWalker ->kode_buku);
            printf("\n-----------------------------------------");
            pWalker = pWalker -> next;
        }
    }else{
        system("cls");
        printf("Tidak Ada Peminjam");
    }
}
void lihatTumpukan(stack *head, rak_buku **head_buku, rak_buku **tail_buku,buku list_buku[3]){
	data_stack *pWalker;
    
    char nama_buku[255], kode_buku[255], pil[2];
	pWalker = (*head).top;
    if((*head).count == 0){
        system("cls");
        printf("Tidak Ada Tumpukan Buku Pengembalian...");
        getch();
    }else{
        for(int i = 0; i < 3; i++){
            if(strcmp(pWalker->kode_buku, list_buku[i].kode_buku) == 0){
                strcpy(nama_buku, list_buku[i].nama_buku);
                strcpy(kode_buku, list_buku[i].kode_buku);
                break;
            }
        }
        int i = 0;
        printf("\n==== Tumpukan Pengembalian Buku yang Belum Dikembalikan ke Rak ====");
        while (pWalker != NULL){
            printf("\n-----------------------------------------");
            printf("\n Nama Buku : %s", list_buku[i].nama_buku);
            printf("\n Kode Buku : %s", pWalker -> kode_buku);
            printf("\n-----------------------------------------");
            pWalker = pWalker -> next;
            i++;
        }
        printf("\nKembalikan Tumpukan Ke Rak Buku? (y/n) : ");
        fflush(stdin);
        gets(pil);
        if(strcmp(pil, "y") == 0){
            tambahBuku(head_buku, tail_buku, nama_buku, kode_buku);
            stackPop(head);
            printf("Mengembalikan Tumpukan Teratas Ke Rak Berhasil...");
            getch();
        }
    }
   
}
