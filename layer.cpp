#include "layer.h"

layer::layer(QString l)
{

    ++idCounter;
    id = idCounter;
    o = new Obraz(w,h);
    blendingModeId = NORMAL;
    opacity = 100;
    blocked = false;
    visible = true;

    pole = w*h;

    if (l.isEmpty())
        label = QString("Warstwa %1").arg(id);
    else
        label = l;
}

int layer::idCounter = -2;
int layer::w = 0;
int layer::h = 0;
int layer::pole = 0;

void layer::setBlocked(bool s)
{
    blocked = s;
}

void layer::setVisible(bool s)
{
    visible = s;
}

bool layer::visibility()
{
    return visible;
}

void layer::setBlendingModeId(int x)
{
    blendingModes id = static_cast<blendingModes>(x);
    blendingModeId = id;
}

void layer::blend(layer *l)
{
    Aopacity = 1.0*l->opacity/100;
    Bopacity = 1.0*opacity/100;


    switch (l->blendingModeId) {
        case NORMAL:
        for (int i = 0; i < pole; ++i) {
            blend_wypelnijZmienne(i,l);
            Br = Aalpha * Ar + Br * (1.0 - Aalpha);
            Bg = Aalpha * Ag + Bg * (1.0 - Aalpha);
            Bb = Aalpha * Ab + Bb * (1.0 - Aalpha);
            blend_zapiszPiksela(i);
        }

        break;

        case MULTIPLY:
        for (int i = 0; i < pole; ++i) {
            blend_wypelnijZmienne(i,l);
            Br = (Aalpha * (Br*Ar)/255) + (1.0 - Aalpha) * Br;
            Bg = (Aalpha * (Bg*Ag)/255) + (1.0 - Aalpha) * Bg;
            Bb = (Aalpha * (Bb*Ab)/255) + (1.0 - Aalpha) * Bb;
            blend_zapiszPiksela(i);
        }
        break;

        case SCREEN:
        for (int i = 0; i < pole; ++i) {
            blend_wypelnijZmienne(i,l);
            Br = (Aalpha * (255 - (((255 - Br) * (255 - Ar)) >> 8)) + (1.0 - Aalpha) * Br);
            Bg = (Aalpha * (255 - (((255 - Bg) * (255 - Ag)) >> 8)) + (1.0 - Aalpha) * Bg);
            Bb = (Aalpha * (255 - (((255 - Bb) * (255 - Ab)) >> 8)) + (1.0 - Aalpha) * Bb);
            blend_zapiszPiksela(i);
        }
        break;

        case OVERLAY: // return (unsigned char)(O * ((L < 128) ? (2 * B * L / 255) : (255 - 2 * (255 - B) * (255 - L) / 255)) + (1.0f - O) * B);
        for (int i = 0; i < pole; ++i) {
            blend_wypelnijZmienne(i,l);
            Br = (Aalpha * ((Ar < 128) ? (2 * Br * Ar / 255) : (255 - 2 * (255 - Br) * (255 - Ar) / 255)) + (1.0 - Aalpha) * Br);
            Bg = (Aalpha * ((Ag < 128) ? (2 * Bg * Ag / 255) : (255 - 2 * (255 - Bg) * (255 - Ag) / 255)) + (1.0 - Aalpha) * Bg);
            Bb = (Aalpha * ((Ab < 128) ? (2 * Bb * Ab / 255) : (255 - 2 * (255 - Bb) * (255 - Ab) / 255)) + (1.0 - Aalpha) * Bb);
            blend_zapiszPiksela(i);
        }
        break;

        case DARKEN: // return (unsigned char)(O * ((L > B) ? B : L) + (1.0f - O) * B);
        for (int i = 0; i < pole; ++i) {
            blend_wypelnijZmienne(i,l);
            Br = (Aalpha * ((Ar > Br) ? Br : Ar) + (1.0 - Aalpha) * Br);
            Bg = (Aalpha * ((Ag > Bg) ? Bg : Ag) + (1.0 - Aalpha) * Bg);
            Bb = (Aalpha * ((Ab > Bb) ? Bb : Ab) + (1.0 - Aalpha) * Bb);
            blend_zapiszPiksela(i);
        }
        break;

        case LIGHTEN: // return (unsigned char)(O * ((L > B) ? L : B) + (1.0f - O) * B);
        for (int i = 0; i < pole; ++i) {
            blend_wypelnijZmienne(i,l);
            Br = (Aalpha * ((Ar > Br) ? Ar : Br) + (1.0 - Aalpha) * Br);
            Bg = (Aalpha * ((Ag > Bg) ? Ag : Bg) + (1.0 - Aalpha) * Bg);
            Bb = (Aalpha * ((Ab > Bb) ? Ab : Bb) + (1.0 - Aalpha) * Bb);
            blend_zapiszPiksela(i);
        }
        break;

        case DIFFERENCE: // (unsigned char)(O * (abs(B - L)) + (1.0f - O) * B);
        for (int i = 0; i < pole; ++i) {
            blend_wypelnijZmienne(i,l);
            Br = (Aalpha * (abs(Br - Ar)) + (1.0 - Aalpha) * Br);
            Bg = (Aalpha * (abs(Bg - Ag)) + (1.0 - Aalpha) * Bg);
            Bb = (Aalpha * (abs(Bb - Ab)) + (1.0 - Aalpha) * Bb);
            blend_zapiszPiksela(i);
        }
        break;

        case ADD: // (unsigned char)(O * (_cpp_min(255, (B + L))) + (1.0f - O) * B);
        for (int i = 0; i < pole; ++i) {
            blend_wypelnijZmienne(i,l);
            Br = (Aalpha * (qMin(255, (Br + Ar))) + (1.0 - Aalpha) * Br);
            Bg = (Aalpha * (qMin(255, (Bg + Ag))) + (1.0 - Aalpha) * Bg);
            Bb = (Aalpha * (qMin(255, (Bb + Ab))) + (1.0 - Aalpha) * Bb);
            blend_zapiszPiksela(i);
        }
        break;

        case SUBSTRACT: // (unsigned char)(O * ((B + L < 255) ? 0 : (B + L - 255)) + (1.0f - O) * B);
        for (int i = 0; i < pole; ++i) {
            blend_wypelnijZmienne(i,l);
            Br = (Aalpha * ((Br + Ar < 255) ? Aalpha : (Br + Ar - 255)) + (1.0f - Aalpha) * Br);
            Bg = (Aalpha * ((Bg + Ag < 255) ? Aalpha : (Bg + Ag - 255)) + (1.0f - Aalpha) * Bg);
            Bb = (Aalpha * ((Bb + Ab < 255) ? Aalpha : (Bb + Ab - 255)) + (1.0f - Aalpha) * Bb);
            blend_zapiszPiksela(i);
        }
        break;
    case AVERAGE: // (unsigned char)(O * ((B + L) / 2) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        Br = (Aalpha * ((Br + Ar) / 2) + (1.0f - Aalpha) * Br);
        Bg = (Aalpha * ((Bg + Ag) / 2) + (1.0f - Aalpha) * Bg);
        Bb = (Aalpha * ((Bb + Ab) / 2) + (1.0f - Aalpha) * Bb);
        blend_zapiszPiksela(i);
    }
    break;
    case NEGATION: // (unsigned char)(O * (255 - abs(255 - B - L)) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        Br = (Aalpha * (255 - abs(255 - Br - Ar)) + (1.0f - Aalpha) * Br);
        Bg = (Aalpha * (255 - abs(255 - Bg - Ag)) + (1.0f - Aalpha) * Bg);
        Bb = (Aalpha * (255 - abs(255 - Bb - Ab)) + (1.0f - Aalpha) * Bb);
        blend_zapiszPiksela(i);
    }
    break;
    case EXCLUSION: //  (unsigned char)(O * (B + L - 2 * B * L / 255) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        Br = (Aalpha * (Br + Ar - 2 * Br * Ar / 255) + (1.0f - Aalpha) * Br);
        Bg = (Aalpha * (Bg + Ag - 2 * Bg * Ag / 255) + (1.0f - Aalpha) * Bg);
        Bb = (Aalpha * (Bb + Ab - 2 * Bb * Ab / 255) + (1.0f - Aalpha) * Bb);
        blend_zapiszPiksela(i);
    }
    case SOFT_LIGHT: // (O * ((L < 128) ? (2 * ((B >> 1) + 64)) * ((float)L / 255) : (255 - (2 * (255 - ((B >> 1) + 64)) * (float)(255 - L) / 255))) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        Br = (Aalpha * ((Ar < 128) ? (2 * ((Br >> 1) + 64)) * ((float)Ar / 255) : (255 - (2 * (255 - ((Br >> 1) + 64)) * (float)(255 - Ar) / 255))) + (1.0f - Aalpha) * Br);
        Bg = (Aalpha * ((Ag < 128) ? (2 * ((Bg >> 1) + 64)) * ((float)Ag / 255) : (255 - (2 * (255 - ((Bg >> 1) + 64)) * (float)(255 - Ag) / 255))) + (1.0f - Aalpha) * Bg);
        Bb = (Aalpha * ((Ab < 128) ? (2 * ((Bb >> 1) + 64)) * ((float)Ab / 255) : (255 - (2 * (255 - ((Bb >> 1) + 64)) * (float)(255 - Ab) / 255))) + (1.0f - Aalpha) * Bb);
        blend_zapiszPiksela(i);
    }
    /*
    case HARD_LIGHT: // (O * ((B < 128) ? (2 * L * B / 255) : (255 - 2 * (255 - L) * (255 - B) / 255)) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        Br =
        blend_zapiszPiksela(i);
    }
    case COLOR_DODGE: // (O * ((L == 255) ? L : _cpp_min(255, ((B << 8 ) / (255 - L)))) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        blend_zapiszPiksela(i);
    }
    case COLOR_BURN: // (O * ((L == 0) ? L : _cpp_max(0, (255 - ((255 - B) << 8 ) / L))) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        blend_zapiszPiksela(i);
    }
    case LINEAR_DODGE: // (O * (_cpp_min(255, (B + L))) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        blend_zapiszPiksela(i);
    }
    break;
    case LINEAR_BURN: // (O * ((B + L < 255) ? 0 : (B + L - 255)) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        blend_zapiszPiksela(i);
    }
    break;
    case LINEAR_LIGHT: // (O * ((2 * L) < 128) ? ((B + (2 * L) < 255) ? 0 : (B + (2 * L) - 255)) : (_cpp_min(255, (B + (2 * (L - 128))))) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        blend_zapiszPiksela(i);
    }
    break;
    case VIVID_LIGHT: // (O * (L < 128) ? (((2 * L) == 0) ? (2 * L) : _cpp_max(0, (255 - ((255 - B) << 8 ) / (2 * L)))) : (_cpp_min(255, (B + (2 * (L - 128))))) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        blend_zapiszPiksela(i);
    }
    break;
    case PIN_LIGHT: // (O * (L < 128) ? (((2 * L) > B) ? B : (2 * L)) : (((2 * (L - 128)) > B) ? (2 * (L - 128)) : B) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        blend_zapiszPiksela(i);
    }
    break;
    case HARD_MIX: // (O * (((L < 128) ? (((2 * L) == 0) ? (2 * L) : _cpp_max(0, (255 - ((255 - B) << 8 ) / (2 * L)))) : (_cpp_min(255, (B + (2 * (L - 128))))) < 128) ? 0 : 255) + (1.0f - O) * B);
    for (int i = 0; i < pole; ++i) {
        blend_wypelnijZmienne(i,l);
        blend_zapiszPiksela(i);
    }
    break;*/
    }
}


void layer::zrobErozje()
{
    /* Miarą stopnia erozji jest wielkość elementu strukturalnego.
     * Im większy element strukturalny tym większa część brzegu podlegającej erozji
     * figury zostaje usunięta.
     *
     *
     * W praktyce operacja erozji jednostkowej odnosi się
     * do usunięcia wszystkich punktów obrazu o wartości 1, które posiadają przynajmniej
     * jeden punkt sąsiedni o wartości 0.
     *
     *
     * Wnioskując z tych definicji erozję można
     * interpretować jako tzw. filtr minimalny, to znaczy taki operator, w którym każdemu
     * punktowi przypisuje się minimalną wartość z punktów jego otoczenia.
     * Dzięki temu pojęcie erozji można rozszerzyć na obrazy posiadające wiele
     * stopni szarości lub kolorowe.
     *
     * Erozję obrazu kolorowego można zdefiniować jako złożenie niezależnych erozji
     * przeprowadzonych na jego poszczególnych składowych (RGB). Wynik erozji obrazu
     * kolorowego może znacznie odbiegać od intuicyjnie spodziewanego rezultatu.
    */


    Obraz *jasnosc = new Obraz(w,h);

    short w2 = w-1;
    short h2 = h-1;
    for (short y = 0; y < h; ++y) {
        for (short x = 0; x < w; ++x) {

            int temp;
            int i, ii, j, jj;
            i = j = -1;
            ii = jj = 1;

            if (y == 0)         i = 0;
            else if (y == h2)   ii = 0;
            if (x == 0)         j = 0;
            else if (x == w2)   jj = 0;

            unsigned char minR, minG, minB;
            minR = minG = minB = 0;

            for (int k = i; k <= ii; ++k) {
                for (int l = j; l <= jj; ++l) {
                    temp = 4*((y+k)*w+(x+l));
                    if (o->dane[temp  ] > minB) minB = o->dane[temp  ];
                    if (o->dane[temp+1] > minG) minG = o->dane[temp+1];
                    if (o->dane[temp+2] > minR) minR = o->dane[temp+2];
                }
            }

            temp = 4*(y*w+x);
            jasnosc->dane[temp+2] = minR;
            jasnosc->dane[temp+1] = minG;
            jasnosc->dane[temp  ] = minB;
            jasnosc->dane[temp+3] = o->dane[temp+3];


        }
    }

    o = jasnosc;

}


void layer::zrobDylatacje()
{
    Obraz *jasnosc = new Obraz(w,h);

    short w2 = w-1;
    short h2 = h-1;
    for (short y = 0; y < h; ++y) {
        for (short x = 0; x < w; ++x) {

            int temp;
            int i, ii, j, jj;
            i = j = -1;
            ii = jj = 1;

            if (y == 0)         i = 0;
            else if (y == h2)   ii = 0;
            if (x == 0)         j = 0;
            else if (x == w2)   jj = 0;

            unsigned char minR, minG, minB;
            minR = minG = minB = 255;

            for (int k = i; k <= ii; ++k) {
                for (int l = j; l <= jj; ++l) {
                    temp = 4*((y+k)*w+(x+l));
                    if (o->dane[temp  ] < minB) minB = o->dane[temp  ];
                    if (o->dane[temp+1] < minG) minG = o->dane[temp+1];
                    if (o->dane[temp+2] < minR) minR = o->dane[temp+2];
                }
            }

            temp = 4*(y*w+x);
            jasnosc->dane[temp+2] = minR;
            jasnosc->dane[temp+1] = minG;
            jasnosc->dane[temp  ] = minB;
            jasnosc->dane[temp+3] = o->dane[temp+3];


        }
    }

    o = jasnosc;

}

