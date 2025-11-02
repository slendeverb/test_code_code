// #include "header.h"

// int screen_width = 100;
// int screen_height = 40;
// float theta_spacin = 0.01;
// float phi_spacin = 0.01;
// float R1 = 1;
// float R2 = 2;
// float K2 = 5;
// float K1 = 50;
// const float pi = 3.1415926535897932;
// float A = pi / 2;
// float B = 0.0;

// int main() {
//     std::cout << "\x1b[2J";
//     while (true) {
//         std::system("cls");
//         std::vector<char> b(screen_width * screen_height, ' ');
//         std::vector<int> c(screen_width * screen_height, 33);
//         std::vector<float> z_buffer(screen_width * screen_height, 0);
//         float cosA = std::cos(A);
//         float cosB = std::cos(B);
//         float sinA = std::sin(A);
//         float sinB = std::sin(B);
//         for (float theta = 0; theta < 2 * pi; theta += theta_spacin) {
//             float cos_theta = std::cos(theta);
//             float sin_theta = std::sin(theta);
//             float a1 = R1 * sin_theta * cosA;
//             float a2 = R2 + R1 * cos_theta;
//             float a3 = R1 * sinA * sin_theta;
//             for (float phi = 0; phi < 2 * pi; phi += phi_spacin) {
//                 float cos_phi = std::cos(phi);
//                 float sin_phi = std::sin(phi);
//                 float x = (a2) * (cosB * cos_phi + sinA * sinB * sin_phi) - a1 * sinB;
//                 float y = (a2) * (sinB * cos_phi - sinA * cosB * sin_phi) + a1 * cosB;
//                 float z = K2 + cosA * (a2)*sin_phi + a3;
//                 float ooz = 1 / z;
//                 int xP = int(screen_width / 2 + K1 * ooz * x);
//                 int yP = int(screen_height / 2 - K1 * ooz * y * 0.5);
//                 float lum =
//                     (cos_phi * cos_theta * sinB - cosA * cos_theta * sin_phi - sinA * sin_theta +
//                      cosB * (cosA * sin_theta - cos_theta * sinA * sin_phi));
//                 if (lum < 0) {
//                     lum = 0;
//                 }
//                 int position = xP + yP * screen_width;
//                 if (position >= 0 && position < screen_width * screen_height) {
//                     if (ooz > z_buffer[position]) {
//                         z_buffer[position] = ooz;
//                         int luminance_index = lum * 8;
//                         b[position] = ".,-~:;=!*#$@"[luminance_index > 0 ? luminance_index : 0];
//                         if (theta > pi + 0.2 * std::cos(phi * 5) &&
//                             theta < 2 * pi - 0.2 * std::cos(phi * 5)) {
//                             c[position] = 95;
//                         }
//                     }
//                 }
//             }
//         }
//         std::cout << "\x1b[H";
//         for (int k = 0; k < screen_width * screen_height; ++k) {
//             std::cout.put(k % screen_width ? b[k] : '\n');
//         }
//         A += 0.1;
//         B += 0.1;
//     }
// }