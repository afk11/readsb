#include "readsb.h"

void init_globe_index(struct tile *s_tiles) {
    int count = 0;

    // Arctic
    s_tiles[count++] = (struct tile) {
        60, -130,
        90, 150
    };

    // North Pacific
    s_tiles[count++] = (struct tile) {
        10, 150,
        90, -130
    };

    // Northern Canada
    s_tiles[count++] = (struct tile) {
        50, -130,
        60, -70
    };

    // Northwest USA
    s_tiles[count++] = (struct tile) {
        40, -130,
        50, -100
    };

    // West Russia
    s_tiles[count++] = (struct tile) {
        40, 20,
        60, 50
    };

    // Central Russia
    s_tiles[count++] = (struct tile) {
        30, 50,
        60, 90
    };

    // East Russia
    s_tiles[count++] = (struct tile) {
        30, 90,
        60, 150
    };

    // Persian Gulf / Arabian Sea
    s_tiles[count++] = (struct tile) {
        10, 50,
        30, 70
    };

    // India
    s_tiles[count++] = (struct tile) {
        10, 70,
        30, 90
    };
    // South China and ICAO special use
    s_tiles[count++] = (struct tile) {
        10, 90,
        30, 150
    };


    // South Atlantic and Indian Ocean
    s_tiles[count++] = (struct tile) {
        -90, -40,
        10, 110
    };

    // Australia
    s_tiles[count++] = (struct tile) {
        -90, 110,
        10, 160
    };

    // South Pacific and NZ
    s_tiles[count++] = (struct tile) {
        -90, 160,
        10, -90
    };

    // North South America
    s_tiles[count++] = (struct tile) {
        -10, -90,
        10, -40
    };

    // South South America
    s_tiles[count++] = (struct tile) {
        -90, -90,
        -10, -40
    };

    // Guatemala / Mexico
    s_tiles[count++] = (struct tile) {
        10, -130,
        30, -90
    };

    // Cuba / Haiti / Honduras
    s_tiles[count++] = (struct tile) {
        10, -90,
        20, -70
    };



    // North Africa
    s_tiles[count++] = (struct tile) {
        10, -10,
        40, 30
    };

    // Middle East
    s_tiles[count++] = (struct tile) {
        10, 30,
        40, 50
    };

    // North Atlantic
    s_tiles[count++] = (struct tile) {
        10, -70,
        60, -10
    };

    if (count + 1 > GLOBE_SPECIAL_INDEX)
        fprintf(stderr, "increase GLOBE_SPECIAL_INDEX please!\n");
}

int globe_index(double lat_in, double lon_in) {
    int grid = GLOBE_INDEX_GRID;
    int lat = grid * ((int) ((lat_in + 90) / grid)) - 90;
    int lon = grid * ((int) ((lon_in + 180) / grid)) - 180;

    struct tile *tiles = Modes.json_globe_special_tiles;

    for (int i = 0; tiles[i].south != 0 || tiles[i].north != 0; i++) {
        struct tile tile = tiles[i];
        if (lat >= tile.south && lat < tile.north) {
            if (tile.west < tile.east && lon >= tile.west && lon < tile.east) {
                return i;
            }
            if (tile.west > tile.east && (lon >= tile.west || lon < tile.east)) {
                return i;
            }
        }
    }


    int i = (lat + 90) / grid;
    int j = (lon + 180) / grid;

    return (i * GLOBE_LAT_MULT + j + 1000);
    // highest number returned: globe_index(90, 180)
    // first 1000 are reserved for special use
}

int globe_index_index(int index) {
    double lat = ((index - 1000) /  GLOBE_LAT_MULT) * GLOBE_INDEX_GRID - 90;
    double lon = ((index - 1000) % GLOBE_LAT_MULT) * GLOBE_INDEX_GRID - 180;
    return globe_index(lat, lon);
}
