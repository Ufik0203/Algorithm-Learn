#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <map>
#include "knapsack.h"
using namespace std;



// ======================================================================
// PERTUKARAN COIN FUNCTION
// ======================================================================

// Fungsi untuk algoritma greedy
void greedy(int amount, vector<int> &coins)
{
  std::sort(coins.begin(), coins.end(), greater<int>());
  map<int, int> count;
  for (int i = 0; i < coins.size(); i++)
  {
    while (amount >= coins[i])
    {
      amount -= coins[i];
      count[coins[i]]++;
    }
  }
  for (auto &coin : coins)
  {
    cout << coin << " = " << count[coin] << endl;
  }
}

// Fungsi untuk algoritma brute force
void bruteForce(int amount, vector<int> &coins, vector<int> &result, vector<int> &temp, int &min, int start = 0)
{
  if (amount == 0)
  {
    if (temp.size() < min)
    {
      min = temp.size();
      result = temp;
    }
    return;
  }
  for (int i = start; i < coins.size(); i++)
  {
    if (coins[i] <= amount)
    {
      temp.push_back(coins[i]);
      bruteForce(amount - coins[i], coins, result, temp, min, i);
      temp.pop_back();
    }
  }
}

// Fungsi untuk menu pertukaran koin
void exchangeCoin()
{

  int n, amount;
  cout << "Masukkan jumlah koin: ";
  cin >> n;
  vector<int> coins(n);
  cout << "Masukkan nilai koin: ";
  for (int i = 0; i < n; i++)
  {
    cin >> coins[i];
  }
  cout << "Masukkan jumlah yang akan ditukar: ";
  cin >> amount;

  int choice;
  cout << "Pilih algoritma pertukaran koin:" << endl;
  cout << "1. Greedy" << endl;
  cout << "2. Brute Force" << endl;
  cout << "3. Keluar\n"
       << endl;
  cout << "Masukkan pilihan: ";
  cin >> choice;

  switch (choice)
  {
  case 1:
  {
    cout << "Hasil algoritma greedy: " << endl;
    greedy(amount, coins);
    cout << "\n"
         << endl;
    break;
  }
  case 2:
  {
    vector<int> result, temp;
    int min = INT_MAX;
    bruteForce(amount, coins, result, temp, min);
    map<int, int> count;
    for (int i = 0; i < result.size(); i++)
    {
      count[result[i]]++;
    }
    cout << "Hasil algoritma brute force: " << endl;
    for (auto &coin : coins)
    {
      cout << coin << " = " << count[coin] << endl;
    }
    cout << "\n"
         << endl;
    break;
  }
  case 3:
    return;
  default:
    cout << "Pilihan tidak valid!" << endl;
    break;
  }
}
// ======================================================================
// PERTUKARAN COIN END
// ======================================================================



// ======================================================================
// JOB SCHEDULING INITIALIZATION
// ======================================================================

// Definisikan struktur untuk tugas
struct Task {
    int id;
    int deadline;
};

// Fungsi perbandingan untuk mengurutkan tugas berdasarkan deadline dalam urutan non-menurun
bool compare(Task a, Task b) {
    return a.deadline < b.deadline;
}


// Function prototypes
void jobSchedulingBruteForce();
void jobSchedulingGreedy();
void selectionSort(int arr[], int n);


// ======================================================================
// JOB SCHEDULING END
// ======================================================================



int main()
{
  while (true)
  {
    int choice;
    int chooseAlgorithm;

    cout << "Menu Utama:" << endl;
    cout << "1. Pertukaran Koin" << endl;
    cout << "2. Job Scheduling" << endl;
    cout << "3. Knapsack Problem" << endl;
    cout << "4. Keluar\n"
         << endl;
    cout << "Masukkan pilihan: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      exchangeCoin();
      break;
    case 2:
       cout << "1. Brute Force" << endl;
            cout << "2. Greedy" << endl;
            cout << "Pilih algoritma : "; 
            cin >> chooseAlgorithm;

            if (chooseAlgorithm == 1) {
                jobSchedulingBruteForce();
            } else if (chooseAlgorithm == 2) {
                jobSchedulingGreedy();
            } else {
                cout << "Pilihan anda tidak di temukan!";
            }
      break;
    case 3:
      run();
      break;
    case 4:
      return 0; // Keluar dari program
    default:
      cout << "Pilihan tidak valid!" << endl;
      break;
    }
  }
}




// ======================================================================
// JOB SCHEDULING FUNCTION
// ======================================================================

// Brute Force implementation
void jobSchedulingBruteForce() {
    int jmlJadwal;
    cout << "Masukkan jumlah jadwal : "; 
    cin >> jmlJadwal;

    // Deklarasi array untuk menyimpan job
    int jobs[jmlJadwal];

    for (int i = 0; i < jmlJadwal; i++) {
        cout << "Masukkan job ke-" << i + 1 << " : "; 
        cin >> jobs[i];
    }

    // Sorting array menggunakan Selection Sort
    selectionSort(jobs, jmlJadwal);

    // Menampilkan isi array setelah sorting
    cout << "\nPrioritas Jadwal Pekerjaan : " << endl;
    for (int i = 0; i < jmlJadwal; i++) {
        cout << "Job : " << jobs[i] << endl;
    }
    cout << endl;
}


// Algoritma greedy untuk menyelesaikan masalah penjadwalan tugas tanpa mempertimbangkan profit
void jobSchedulingGreedy() {
    int n; // Jumlah tugas
    cout << "Masukkan jumlah jadwal : ";
    cin >> n;

    // Membuat vektor untuk menyimpan tugas
    vector<Task> tasks(n);

    // Memasukkan detail setiap tugas
    for (int i = 0; i < n; ++i) {
        cout << "Masukkan job ke-" << i + 1 << " : ";
        cin >> tasks[i].deadline;
        tasks[i].id = i + 1; // Mengisi id tugas
    }

    // Mengurutkan tugas berdasarkan deadline dalam urutan non-menurun
    sort(tasks.begin(), tasks.end(), compare);

    // Inisialisasi array untuk menyimpan jadwal yang dipilih
    vector<bool> slot(n, false);

    // Memilih tugas dengan algoritma greedy
    int scheduledTasks = 0;
    cout << "Prioritas Jadwal Pekerjaan : ";
    for (int i = 0; i < n; ++i) {
        for (int j = min(n, tasks[i].deadline) - 1; j >= 0; --j) {
            if (!slot[j]) {
                cout << tasks[i].id << " ";
                slot[j] = true;
                scheduledTasks++;
                break;
            }
        }
    }
    cout << endl;
    cout << "Jumlah pekerjaan yang dijadwalkan : " << scheduledTasks << endl;
}



// Selection Sort implementation
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}


// ======================================================================
// JOB SCHEDULING END
// ======================================================================
