#ifndef GERAK_TARI_H
#define GERAK_TARI_H


#include <program_rekam_gerak/tangan_controller.h>
#include <program_rekam_gerak/communication_manager.h>

#include <ryml.hpp>
#include <ryml_std.hpp>

#include <iomanip>
#include <sstream>

#include <std_msgs/msg/string.hpp>

/* CUSTOM DATA STRUCTURE FOR GERAK TARI */
struct MotionFrame {
    int tangan;
    // kepala, kaki, dll menyusul
    unordered_map<string, int> kepala;
};


struct GerakTari {
    string name;
    bool is_walking;
    float speeds;
    int times;
    std::vector<MotionFrame> motion_frames;
};

#define PATH_TO_CONFIG BASE_PATH "gerak_tari.yaml"


class GerakTariHandler: public rclcpp::Node {
    private:
    string variasi_gerak_pressed;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subs_variasi_gerak;

    std::vector<GerakTari> list_of_gerak_tari;
    int gerak_tari_size = 0; // Digunakan untuk menyimpan total gerak tari yang ada
    int mute_on_walk_counter = 0; // Menghitung berapa banyak mute ketika walk [int mute di program lama]
    std::vector<GerakTari> muted_walks; // List berisi walk yang akan dijalankan karena sebelumnya di-mute [array data_replace di program lama]
    std::vector<GerakTari> shifted_next_walk_moves; // List berisi gerak tari (jalan) selanjutnya yang dipindah urutannya agar tidak hilang karena kondisi setelah mute [array data_shift di program lama]
    int shift_next_walk_counter = 0; // Menghitung berapa gerak tari (jalan) selanjutnya yang perlu dipindah urutannya [int shift di program lama]
    int last_mute_index = 0; // Menyimpan index terakhir gerak tari yang di-mute [int last_mute di program lama]
    
    TanganController tanganController;

    std::string read_file(const char *filename);
    void execute_move(GerakTari gerak_tari);


    public:
    GerakTariHandler();
    ~GerakTariHandler();
    void preload_config(const char* config_path = PATH_TO_CONFIG);
    void play();
    void setDefaultPose();
    void pingServos();
    void setTorqueOn();
    void setTorqueOff();
    bool isVariasiBtnHasPressed();
};


#endif

