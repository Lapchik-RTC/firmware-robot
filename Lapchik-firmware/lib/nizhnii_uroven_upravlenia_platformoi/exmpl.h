// // Encoder.h

// class ENC
// {
// public:
//     void get_angle();
// }


// // Motor.h

// class MOTOR
// {
// public:
//     void set_u(float u);
// };

// // Servo.h

// #include "Encoder.h"
// #include "Motor.h"

// class SERVO
// {
// private:
//     ENC *enc; // Объявление полей указателей на существующие энкодер и мотор
//     MOTOR *m; // Создание "полочек", на которых будут лежать указатели на сущетсвующие энкодер и мотор

// public:
//     SERVO(ENC *enc_, MOTOR *m_)
//     {
//         enc = enc_; // Сохранение указателей на существующие энкодер и мотор
//         m = m_; // Кладем на эти "полочки" листики с указанием где эти мотор и энкодер искать когда они нам понадобятся
//     }
//     void set_angle(float angle);
//     void tick()
//     {
//         float angle_now = enc->get_angle();
//         m->set_u(angle_now * 1231451);
//     }
// }

// ENC enc1, enc2;
// MOTOR m1, m2;

// SERVO s1(&enc1, &m1), s2(&enc2, &m2);
