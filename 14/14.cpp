#include "../lib.hpp"

struct robot { int px, py, vx, vy; };

int main() {
    vector<robot> robots;
    int w = 101, h = 103, w2 = w / 2, h2 = h / 2;

    const regex linerex("p=(.*),(.*) v=(.*),(.*)");
    while (true) {
        string s;
        getline(cin, s);
        if (!cin) break;

        smatch linematch;
        if (regex_match(s, linematch, linerex) && linematch.size() == 5) {
            int px = stoi(linematch[1].str());
            int py = stoi(linematch[2].str());
            int vx = stoi(linematch[3].str());
            int vy = stoi(linematch[4].str());
            robots.emplace_back(robot { px, py, vx, vy });
        }
    }

    png::image<png::index_pixel> image;
    png::palette pal(2);
    pal[0] = png::color(255, 255, 255);
    pal[1] = png::color(0, 0, 0);
    image.set_palette(pal);
    image.resize(w*w, h*h);

    for (png::uint_32 y = 0; y < image.get_height(); ++y)
        for (png::uint_32 x = 0; x < image.get_width(); ++x)
            image[y][x] = png::index_pixel(0);

    for (int t = 0; t < w * h; t++) {
        int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
        int qx = (t % w) * w, qy = (t / w) * h;
        for (robot &r : robots) {
            if (r.px < w2 && r.py < h2) q1++;
            if (r.px < w2 && r.py > h2) q2++;
            if (r.px > w2 && r.py < h2) q3++;
            if (r.px > w2 && r.py > h2) q4++;
            image[qy + r.py][qx + r.px] = png::index_pixel(1);
        }

        if (t == 100)
            cout << q1*q2*q3*q4 << endl;

        for (robot &r : robots) {
            r.px = (r.px + r.vx) % w;
            if (r.px < 0) r.px += w;
            r.py = (r.py + r.vy) % h;
            if (r.py < 0) r.py += h;
        }
    }

    image.write("output.png");

    return 0;
}

