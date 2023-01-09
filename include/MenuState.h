#ifndef MENU_STATE
#define MENU_STATE
enum MenuState
{
    LOOPS = 0,
    PAN = 1,
    INPUT_VOLUMES = 2,
    OUTPUT_VOLUMES = 3,
    DELAY_TRILS = 4,
    PHASE = 5,
    NUM_MAIN_MENU_OPTIONS = 6, // FOR BUTTON PRESS CYCLING
    BANKS = 7,
    SAVE_PRESET = 8
};
#endif // MENU_STATE