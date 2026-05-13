/**
 * PRAKTIKUM SMART AGRICULTURE (IRIGASI OTOMATIS)
 * Mikrokontroler : ESP32
 * Sensor         : Potensiometer di Pin 34 (Simulasi Kelembaban Tanah)
 * Aktuator       : Modul Relay di Pin 27 (Simulasi Pompa Air / LED)
 */

// --- 1. DEKLARASI PIN ---
const int PIN_SENSOR = 34;  // Pin analog untuk membaca Potensiometer
const int PIN_RELAY  = 27;  // Pin digital untuk mengontrol Modul Relay

// --- 2. PENGATURAN AMBANG BATAS (THRESHOLD) ---
// Nilai ADC ESP32 adalah 0 - 4095.
// Asumsi simulasi: 0 = Sangat Basah, 4095 = Sangat Kering.
// Kita tetapkan batas 2500. Jika di atas 2500, tanah dianggap butuh air.
const int THRESHOLD_KERING = 2500; 

void setup() {
  // Inisialisasi komunikasi serial untuk monitoring data di layar
  Serial.begin(115200);
  
  // Konfigurasi mode pin
  pinMode(PIN_SENSOR, INPUT);
  pinMode(PIN_RELAY, OUTPUT);
  
  // Memastikan pompa (Relay) dalam keadaan mati saat sistem pertama kali menyala
  digitalWrite(PIN_RELAY, LOW);
  
  Serial.println("=== Sistem Irigasi Cerdas Diinisialisasi ===");
  Serial.println("Memulai pembacaan kondisi tanah...\n");
  delay(1000); // Jeda 1 detik sebelum masuk ke fungsi loop
}

void loop() {
  // --- 3. AKUISISI DATA ---
  // Membaca nilai dari Potensiometer (0 - 4095)
  int nilaiKelembaban = analogRead(PIN_SENSOR);
  
  // Menampilkan nilai numerik ke Serial Monitor
  Serial.print("Data Sensor Tanah: ");
  Serial.print(nilaiKelembaban);

  // --- 4. LOGIKA PENGAMBILAN KEPUTUSAN (KONTROL POMPA) ---
  if (nilaiKelembaban > THRESHOLD_KERING) {
    // Kondisi: Tanah Kering
    digitalWrite(PIN_RELAY, HIGH); // Mengaktifkan Relay (Pompa / LED Menyala)
    Serial.println(" -> Status: KERING | Pompa: MENYALA");
  } 
  else {
    // Kondisi: Tanah Basah / Cukup Air
    digitalWrite(PIN_RELAY, LOW);  // Mematikan Relay (Pompa / LED Padam)
    Serial.println(" -> Status: BASAH  | Pompa: MATI");
  }

  // --- 5. JEDA PENGIRIMAN DATA ---
  // Jeda 1 detik agar data tidak terlalu cepat memenuhi layar Serial Monitor
  // Pada implementasi IoT sungguhan, jeda ini bisa diatur setiap 5 atau 10 menit.
  delay(1000); 
}
