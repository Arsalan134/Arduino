#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

enum _ttype {
    PCB,
    LOWHIP,
    PA1WHIP_HANGING,
    PA1WHIP_STRAIGHT,
    PA1WHIP_JAMMED,
    PA2WHIP,
    PA2WHIPBS,
    PA2SHORTWHIP,
    PA2WHIPPOINTING,
    PA2WHIPNOTPOINTING,
    PA2WHIPCAP,
    PA2SHORTWHIPCAP,
    PA2TX,
    PA2RX
};

string getName(_ttype t) {
    switch (t) {
    case PCB: return "PCB";
    case LOWHIP: return "Lo-whip";
    case PA1WHIP_HANGING: return "PA1-whip hanging";
    case PA1WHIP_STRAIGHT: return "PA1-whip straight";
    case PA1WHIP_JAMMED: return "PA1-whip jammed";
    case PA2WHIP: return "PA2-whip";
    case PA2WHIPPOINTING: return "PA2-whip-pointing";
    case PA2WHIPNOTPOINTING: return "PA2-whip-not-pointing";
    case PA2WHIPBS: return "PA2-whip-dmg";
    case PA2WHIPCAP: return "PA2-whip-cap";
    case PA2SHORTWHIP: return "PA2-shortwhip";
    case PA2SHORTWHIPCAP: return "PA2-shortwhip-cap";
    case PA2TX: return "PA2-TX";
    case PA2RX: return "PA2-RX";
    }
    return "XXX";
}

class Range {

public:

    float counts[3000];
    float values[3000];
    string filename;
    _ttype tx;
    _ttype rx;

    Range(string f, _ttype _tx, _ttype _rx) { filename = f; rx = _rx; tx = _tx; }

    string getDisplayName() {
        return getName(tx) + " - " + getName(rx);
    }

    void read() {

        FILE* f = fopen((string("/home/chris/tmp/grabRangeTestFiles/apps/com.iforce2d.nrf24rangetest/f/")+filename).c_str(), "rb");

        int count = 0;
        float val;
        while (fread(&val, sizeof(float), 1, f) == 1 && count < 2999) {
            char* p = (char*)&val;
            char t = p[0];
            p[0] = p[3];
            p[3] = t;
            t = p[1];
            p[1] = p[2];
            p[2] = t;
            //printf("Count %d : %f\n", count, val);

            counts[count] = val;

            count++;
        }

        count = 0;

        while (fread(&val, sizeof(float), 1, f) == 1 && count < 3000) {
            char* p = (char*)&val;
            char t = p[0];
            p[0] = p[3];
            p[3] = t;
            t = p[1];
            p[1] = p[2];
            p[2] = t;
            //printf("Value %d : %f\n", count, val);

            values[count] = val;

            count++;
        }

        fclose(f);

        // fill empty spots
        for (int i = 0; i < 2000; i++) {
            if (values[i] > 0)
                continue;
            int p = i-1;
            int n = i+1;
            while (p > 0    && values[p] == 0) p--;
            while (n < 2000 && values[n] == 0) n++;
            if (p != 0 && n != 2000) {
                int r = n-p;
                int r1 = i-p;
                int r2 = n-i;
                values[i] = values[p] + r1/(float)r * (values[n] - values[p]);
            }
            else if (n != 2000) {
                values[i] = values[n];
            }
        }

        values[0] = values[1];

    }

    void output() {
        printf("Distance (m), PPS\n");
        for (int i = 0; i < 1500; i++) {
            //if ( counts[i] > 0 ) {
            printf("%d, %f\n", i, values[i]);
            //}
        }
    }

};

int main(int argc, char *argv[]) {

    vector<Range*> ranges;

    ranges.push_back( new Range("pcbpcb", PCB, PCB) );
    ranges.push_back( new Range("pcbloducky", PCB, LOWHIP) );
    ranges.push_back( new Range("pcbhiducky", PCB, PA2WHIP) );
    ranges.push_back( new Range("loduckyhiducky", LOWHIP, PA2WHIP) );
    ranges.push_back( new Range("loduckypcb", LOWHIP, PCB) );
    ranges.push_back( new Range("hiducky1pcb", PA1WHIP_HANGING, PCB) );
    ranges.push_back( new Range("hiducky1loducky", PA1WHIP_HANGING, LOWHIP) );
    ranges.push_back( new Range("hiducky2pcb", PA2WHIP, PCB) );
    ranges.push_back( new Range("t2hi2duckyhi2ducky", PA2WHIP, PA2WHIP) );
    ranges.push_back( new Range("t2hi2duckyloducky", PA2WHIP, LOWHIP) );
    ranges.push_back( new Range("t2hi2leaftxhi2leafrx", PA2TX, PA2RX) );
    ranges.push_back( new Range("t2hi2leaftxpcb", PA2TX, PCB) );
    ranges.push_back( new Range("t2hi2leafrxhi2leaftx", PA2RX, PA2TX) );
    ranges.push_back( new Range("t2hi2leafrxpcb", PA2RX, PCB) );
    ranges.push_back( new Range("t3hi1clearhi2ducky", PA1WHIP_STRAIGHT, PA2WHIP) );
    ranges.push_back( new Range("t3hi1clearpcb", PA1WHIP_STRAIGHT, PCB) );
    ranges.push_back( new Range("t3hi1jammedhi2ducky", PA1WHIP_JAMMED, PA2WHIP) );
    ranges.push_back( new Range("t3hi1jammedpcb", PA1WHIP_JAMMED, PCB) );

    ranges.push_back( new Range("t4longwhiplongwhip", PA2WHIP, PA2WHIP) );
    ranges.push_back( new Range("t4longwhipshortwhip", PA2WHIP, PA2SHORTWHIP) );
    ranges.push_back( new Range("t4shortwhiplongwhip", PA2SHORTWHIP, PA2WHIP) );
    ranges.push_back( new Range("t4shortwhipshortwhip", PA2SHORTWHIP, PA2SHORTWHIP) );

    ranges.push_back( new Range("t5BSlongwhiplongwhip", PA2WHIPBS, PA2WHIP) );
    ranges.push_back( new Range("t5BSlongwhipshortwhip", PA2WHIPBS, PA2SHORTWHIP) );

    ranges.push_back( new Range("t5longwhiplongwhip", PA2WHIP, PA2WHIP) );
    ranges.push_back( new Range("t5longwhipshortwhip", PA2WHIP, PA2SHORTWHIP) );

    ranges.push_back( new Range("t6caplongwhipcaplongwhip", PA2WHIPCAP, PA2WHIPCAP) );
    ranges.push_back( new Range("t6caplongwhipcapshortwhip", PA2WHIPCAP, PA2SHORTWHIPCAP) );

    ranges.push_back( new Range("whipnotpointing", PA2WHIP, PA2WHIPNOTPOINTING) );
    ranges.push_back( new Range("whippointing", PA2WHIP, PA2WHIPPOINTING) );

    printf("Distance (m), ");
    for (int i = 0; i < ranges.size(); i++) {
        Range* r = ranges[i];
        r->read();
        printf("%s, ", r->getDisplayName().c_str());
    }
    printf("\n");
    for (int i = 0; i < 1660; i++) {
        printf("%d, ", i);
        for (int k = 0; k < ranges.size(); k++) {
            Range* r = ranges[k];
            printf("%f, ", r->values[i]);
        }
        printf("\n");
    }

    return 0;
}


