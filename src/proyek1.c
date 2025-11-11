#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BARANG 100
#define MAX_TANGGAL 20
#define MAX_NAMA_BARANG 50

char daftar_nama_barang[MAX_BARANG][MAX_NAMA_BARANG];
int daftar_stok[MAX_BARANG];
float daftar_harga[MAX_BARANG];

char daftar_tanggal[MAX_TANGGAL][MAX_TANGGAL];
char daftar_transaksi_barang[MAX_TANGGAL][MAX_NAMA_BARANG];
int daftar_jumlah_transaksi[MAX_TANGGAL];

int jumlah_barang = 0;
int jumlah_transaksi = 0;

void tambahStok(char nama_barang[MAX_NAMA_BARANG], int jumlah, float harga) {
    for (int i = 0; i < jumlah_barang; i++) {
        if (strcmp(daftar_nama_barang[i], nama_barang) == 0) {
            daftar_stok[i] += jumlah;
            printf("Stok %s berhasil ditambahkan sebanyak %d. Stok sekarang: %d\n", nama_barang, jumlah, daftar_stok[i]);
            return;
        }
    }

    
    strcpy(daftar_nama_barang[jumlah_barang], nama_barang);
    daftar_stok[jumlah_barang] = jumlah;
    daftar_harga[jumlah_barang] = harga;
    jumlah_barang++;
    printf("Barang %s berhasil ditambahkan ke dalam stok sebanyak %d. Stok sekarang: %d\n", nama_barang, jumlah, daftar_stok[jumlah_barang - 1]);
}

void catatPenjualan(char nama_barang[MAX_NAMA_BARANG], int jumlah, char tanggal[MAX_TANGGAL]) {
    for (int i = 0; i < jumlah_barang; i++) {
        if (strcmp(daftar_nama_barang[i], nama_barang) == 0) {
            if (daftar_stok[i] >= jumlah) {
                strcpy(daftar_tanggal[jumlah_transaksi], tanggal);
                strcpy(daftar_transaksi_barang[jumlah_transaksi], nama_barang);
                daftar_jumlah_transaksi[jumlah_transaksi] = jumlah;

                daftar_stok[i] -= jumlah;
                jumlah_transaksi++;

                printf("Penjualan %s sebanyak %d pada tanggal %s berhasil dicatat. Stok sekarang: %d\n", nama_barang, jumlah, tanggal, daftar_stok[i]);
            } else {
                printf("Stok %s tidak mencukupi untuk melakukan penjualan sebanyak %d. Stok sekarang: %d\n", nama_barang, jumlah, daftar_stok[i]);
            }
            return;
        }
    }

    
    printf("Barang %s tidak ditemukan dalam stok.\n", nama_barang);
}

void buatLaporan(char jenis_laporan[MAX_TANGGAL], FILE *filePointer) {
    printf("\n=======Laporan %s:========\n", jenis_laporan);
    fprintf(filePointer,"Laporan %s:\n", jenis_laporan);


    
    for (int i = 0; i < jumlah_transaksi - 1; i++) {
        for (int j = 0; j < jumlah_transaksi - i - 1; j++) {
            if (strcmp(daftar_tanggal[j], daftar_tanggal[j + 1]) > 0) {
               
                char temp_tanggal[MAX_TANGGAL];
                strcpy(temp_tanggal, daftar_tanggal[j]);
                strcpy(daftar_tanggal[j], daftar_tanggal[j + 1]);
                strcpy(daftar_tanggal[j + 1], temp_tanggal);

                char temp_barang[MAX_NAMA_BARANG];
                strcpy(temp_barang, daftar_transaksi_barang[j]);
                strcpy(daftar_transaksi_barang[j], daftar_transaksi_barang[j + 1]);
                strcpy(daftar_transaksi_barang[j + 1], temp_barang);

                int temp_jumlah = daftar_jumlah_transaksi[j];
                daftar_jumlah_transaksi[j] = daftar_jumlah_transaksi[j + 1];
                daftar_jumlah_transaksi[j + 1] = temp_jumlah;
            }
        }
    }

    for (int i = 0; i < jumlah_transaksi; i++) {
        if (strstr(daftar_tanggal[i], jenis_laporan) != NULL) {
            fprintf(filePointer,"%s: %s sebanyak %d dengan harga %.2f\n", daftar_tanggal[i], daftar_transaksi_barang[i], daftar_jumlah_transaksi[i], daftar_harga[i]);
            
            printf("%s: %s sebanyak %d dengan harga %.2f\n", daftar_tanggal[i], daftar_transaksi_barang[i], daftar_jumlah_transaksi[i], daftar_harga[i]);
        }
    }
}

void lihatStok(FILE *filePointer) {
    printf("Stok Barang:\n");
    fprintf(filePointer,"Stok Barang:\n");


    for (int i = 0; i < jumlah_barang; i++) {
        printf("%s: %d dengan harga %.2f\n", daftar_nama_barang[i], daftar_stok[i], daftar_harga[i]);
        fprintf(filePointer,"%s: %d dengan harga %.2f\n", daftar_nama_barang[i], daftar_stok[i], daftar_harga[i]);


    }
}

void lihatSemuaTransaksi(FILE *filePointer) {
    printf("Semua Transaksi:\n");
    fprintf(filePointer,"Semua Transaksi:\n");



    for (int i = 0; i < jumlah_transaksi; i++) {
        fprintf(filePointer,"%s: %s sebanyak %d dengan harga %.2f\n", daftar_tanggal[i], daftar_transaksi_barang[i], daftar_jumlah_transaksi[i], daftar_harga[i]);
        
        printf("%s: %s sebanyak %d dengan harga %.2f\n", daftar_tanggal[i], daftar_transaksi_barang[i], daftar_jumlah_transaksi[i], daftar_harga[i]);
    }
}

void tampilkanMenu() {
    printf("\n===== Menu Toko U.D. Antony =====\n");
    printf("1. Tambah Stok Barang\n");
    printf("2. Catat Penjualan\n");
    printf("3. Lihat Laporan\n");
    printf("4. Lihat Stok Barang\n");
    printf("5. Lihat Semua Transaksi\n");
    printf("6. Keluar\n");
    printf("Pilih menu (1-6): ");
}

int main() {
    FILE *filePointer;
    filePointer = fopen("proyek.txt", "w");
    if (filePointer == NULL) {
        printf("Error opening file.\n");
        return 1; 
    }
    fclose(filePointer);

    int pilihan;
    char nama_barang[MAX_NAMA_BARANG];
    int jumlah;
    float harga;
    char tanggal[MAX_TANGGAL];
    char jenis_laporan[MAX_TANGGAL];

    do {
        tampilkanMenu();
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                filePointer = fopen("proyek.txt", "a");
                printf("Masukkan nama barang: ");
                scanf("%s", nama_barang);
                fprintf(filePointer, "nama barang: %s\n", nama_barang);
                printf("Masukkan jumlah stok yang ditambahkan: ");
                scanf("%d", &jumlah);
                fprintf(filePointer, "Jumlah barang: %d\n", jumlah);
                printf("Masukkan harga barang: ");
                scanf("%f", &harga);
                fprintf(filePointer, "Harga barang: %f\n", harga);
                fclose(filePointer);
                tambahStok(nama_barang, jumlah, harga);
                break;

            case 2:
                filePointer = fopen("proyek.txt", "a");
                printf("Masukkan nama barang: ");
                scanf("%s", nama_barang);
                printf("Masukkan jumlah penjualan: ");
                scanf("%d", &jumlah);
                printf("Masukkan tanggal penjualan (YYYY-MM-DD): ");
                scanf("%s", tanggal);
                fclose(filePointer);
                catatPenjualan(nama_barang, jumlah, tanggal);
                break;

            case 3:
                filePointer = fopen("proyek.txt", "a");
                printf("Pilih jenis laporan:\n");
                printf("1. Harian\n");
                printf("2. Mingguan\n");
                printf("3. Bulanan\n");
                printf("4. Tahunan\n");
                printf("Pilih jenis laporan (1-4): ");
                int jenis;
                scanf("%d", &jenis);

                switch (jenis) {
                    case 1:
                        filePointer = fopen("proyek.txt", "a");
                        printf("Masukkan tanggal laporan (YYYY-MM-DD): ");
                        scanf("%s", jenis_laporan);
                        buatLaporan(jenis_laporan, filePointer);
                        break;

                    default:
                        printf("Pilihan tidak valid. Silakan pilih lagi.\n");
                }
                fclose(filePointer);
                break;

            case 4:
                filePointer = fopen("proyek.txt", "a");
                fprintf(filePointer, "\n===== Lihat Stok Barang =====\n");
                lihatStok(filePointer);
                fclose(filePointer);
                break;

            case 5:
                filePointer = fopen("proyek.txt", "a");
                fprintf(filePointer, "\n===== Lihat Semua Transaksi =====\n");
                lihatSemuaTransaksi(filePointer);
                fclose(filePointer);
                break;

            case 6:
                printf("Terima kasih. Program selesai.\n");
                break;

            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
        }
    } while (pilihan != 6);
 return 0;
}
