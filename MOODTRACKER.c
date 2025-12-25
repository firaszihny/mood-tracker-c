#include <stdio.h>
#include <string.h>

struct Mood {
    char date[15];   // YYYY-MM-DD
    char mood[20];
    char note[100];
};

struct Mood dataMood[200];
int jumlahData = 0;

/* ===== FUNCTION ===== */

void addMood() {
    if (jumlahData >= 200) {
        printf("Data penuh!\n");
        return;
    }

    printf("Tanggal (YYYY-MM-DD): ");
    scanf("%s", dataMood[jumlahData].date);

    printf("Mood: ");
    scanf("%s", dataMood[jumlahData].mood);

    printf("Catatan: ");
    scanf(" %[^\n]", dataMood[jumlahData].note);

    jumlahData++;
    printf("Mood berhasil ditambahkan!\n");
}

void showAll() {
    if (jumlahData == 0) {
        printf("Belum ada data.\n");
        return;
    }

    for (int i = 0; i < jumlahData; i++) {
        printf("\nData ke-%d\n", i + 1);
        printf("Tanggal : %s\n", dataMood[i].date);
        printf("Mood    : %s\n", dataMood[i].mood);
        printf("Catatan : %s\n", dataMood[i].note);
    }
}

void searchByDate() {
    char cari[15];
    int found = 0;

    printf("Masukkan tanggal: ");
    scanf("%s", cari);

    for (int i = 0; i < jumlahData; i++) {
        if (strcmp(dataMood[i].date, cari) == 0) {
            printf("\nTanggal : %s\n", dataMood[i].date);
            printf("Mood    : %s\n", dataMood[i].mood);
            printf("Catatan : %s\n", dataMood[i].note);
            found = 1;
        }
    }

    if (!found)
        printf("Data tidak ditemukan.\n");
}

void searchByKeyword() {
    char key[50];
    int found = 0;

    printf("Masukkan keyword: ");
    scanf(" %[^\n]", key);

    for (int i = 0; i < jumlahData; i++) {
        if (strstr(dataMood[i].note, key)) {
            printf("\nTanggal : %s\n", dataMood[i].date);
            printf("Mood    : %s\n", dataMood[i].mood);
            printf("Catatan : %s\n", dataMood[i].note);
            found = 1;
        }
    }

    if (!found)
        printf("Keyword tidak ditemukan.\n");
}

void sortByDate() {
    struct Mood temp;

    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = i + 1; j < jumlahData; j++) {
            if (strcmp(dataMood[i].date, dataMood[j].date) > 0) {
                temp = dataMood[i];
                dataMood[i] = dataMood[j];
                dataMood[j] = temp;
            }
        }
    }

    printf("Data diurutkan berdasarkan tanggal.\n");
}

void sortByMood() {
    struct Mood temp;

    for (int i = 0; i < jumlahData - 1; i++) {
        for (int j = i + 1; j < jumlahData; j++) {
            if (strcmp(dataMood[i].mood, dataMood[j].mood) > 0) {
                temp = dataMood[i];
                dataMood[i] = dataMood[j];
                dataMood[j] = temp;
            }
        }
    }

    printf("Data diurutkan berdasarkan mood.\n");
}

void analyzeMood() {
    char moodList[200][20];
    int count[200] = {0};
    int totalMood = 0;

    for (int i = 0; i < jumlahData; i++) {
        int found = 0;
        for (int j = 0; j < totalMood; j++) {
            if (strcmp(moodList[j], dataMood[i].mood) == 0) {
                count[j]++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(moodList[totalMood], dataMood[i].mood);
            count[totalMood]++;
            totalMood++;
        }
    }

    int max = 0;
    printf("\n=== ANALISIS MOOD ===\n");
    for (int i = 0; i < totalMood; i++) {
        printf("%s : %d kali\n", moodList[i], count[i]);
        if (count[i] > count[max])
            max = i;
    }

    printf("Mood Dominan: %s\n", moodList[max]);
}

void saveToFile() {
    FILE *fp = fopen("mood_data.txt", "w");
    for (int i = 0; i < jumlahData; i++) {
        fprintf(fp, "%s|%s|%s\n",
                dataMood[i].date,
                dataMood[i].mood,
                dataMood[i].note);
    }
    fclose(fp);
    printf("Data tersimpan ke file.\n");
}

void loadFromFile() {
    FILE *fp = fopen("mood_data.txt", "r");
    if (!fp) return;

    jumlahData = 0;
    while (fscanf(fp, "%[^|]|%[^|]|%[^\n]\n",
                  dataMood[jumlahData].date,
                  dataMood[jumlahData].mood,
                  dataMood[jumlahData].note) != EOF) {
        jumlahData++;
    }
    fclose(fp);
}

/* ===== MAIN ===== */

int main() {
    int menu;
    loadFromFile();

    do {
        printf("\n===== MOOD TRACKER =====\n");
        printf("1. Tambah Mood\n");
        printf("2. Lihat Semua Mood\n");
        printf("3. Cari Mood (Tanggal)\n");
        printf("4. Cari Catatan\n");
        printf("5. Urutkan Tanggal\n");
        printf("6. Urutkan Mood\n");
        printf("7. Analisis Mood\n");
        printf("8. Simpan ke File\n");
        printf("0. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &menu);

        switch (menu) {
            case 1: addMood(); break;
            case 2: showAll(); break;
            case 3: searchByDate(); break;
            case 4: searchByKeyword(); break;
            case 5: sortByDate(); break;
            case 6: sortByMood(); break;
            case 7: analyzeMood(); break;
            case 8: saveToFile(); break;
        }
    } while (menu != 0);

    saveToFile();
    return 0;
}