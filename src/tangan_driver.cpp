#include <program_rekam_gerak/gerak_tari.h>

GerakTariHandler gerakTariHandler;
string config_name;
string fullpath_config;

void cobaGerakTangan() {
    printf("'q' - Quit\n'd' - Default\n'Space' - Play Gerak Tari\n");
    printf("'i' - Ping MX28 dan XL320\n");
    printf("'o' - Torque On\n");
    printf("'p' - Torque Off\n");

    if (TerminalHelper::key_pressed == 'd') {
        // Set Posisi Tangan Default
        cout << "Default Pose" << endl;
        gerakTariHandler.tanganController.toDefaultPose();
    }
    else if (TerminalHelper::key_pressed == ' ') {
        cout << "Playing Tari" << endl;
        std::vector<GerakTari> gerak_tari_var_kiri;
        // Preload config gerak tari harapannya akan dijalankan ketika program dimulai
        gerakTariHandler.preload_config(fullpath_config.c_str());
        gerakTariHandler.play();

        cout << "Tari Selesai\n\n";
    }
    else if (TerminalHelper::key_pressed == 'i') {
        gerakTariHandler.tanganController.pingMX28();
        gerakTariHandler.tanganController.pingXL320();
    }
    else if (TerminalHelper::key_pressed == 'o') {
        gerakTariHandler.tanganController.setTorqueOn();
    }
    else if (TerminalHelper::key_pressed == 'p') {
        gerakTariHandler.tanganController.setTorqueOff();
    }
}


int main(int argc, char** argv) {
    if (argc > 1) {
        config_name = argv[1];
    }
    else {
        config_name = "";
    }
    fullpath_config = BASE_PATH + string("config_tari/") + config_name + ".yaml";

    TerminalHelper::buildTerminalLoop(cobaGerakTangan);

    return 0;
}
