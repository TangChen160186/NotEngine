#include <stdio.h>
#include <stdlib.h>

#include "core/logger/log.h"
#include "core/mathematics/math_funcs.h"
#include "core/mathematics/matrix4x4.h"
#include "core/mathematics/quaternion.h"
#include "core/mathematics/vector2.h"
#include "core/mathematics/vector3.h"

int main(void) {
    
    init_log_system();
    Vector3 a = vector3_create(1, 0,0);
    Quaternion q = quaternion_create_from_yaw_pitch_roll(0, math_to_radians(45), math_to_radians(45));
    Matrix4x4 afa=Matrix44_CreateFromQuaternion(q);
    Quaternion fa = quaternion_create_from_rotation_matrix(afa);


    Quaternion q1 = quaternion_create_from_axis_angle(0, 0,1,math_to_radians(135));
    Vector3 res = quaternion_transform_vector3(q1, a);

    Matrix4x4 m=Matrix44_Identity();
    Quaternion r1 = quaternion_create_from_yaw_pitch_roll(0, 0, math_to_radians(45));
    Matrix4x4 r = Matrix44_CreateFromQuaternion(r1);
    Matrix4x4 s = Matrix44_CreateScale(1, 1, 1);
    Matrix4x4 t = Matrix44_CreateTranslation(1, 2, 3);
    Matrix4x4 srt = Matrix44_Product(s,Matrix44_Product(r, t));
    Vector3 scale;
    Vector3 translation;
    Quaternion rotation;
    Vector3 adaf=Matrix44_TransformVector3(srt, (Vector3){ 1,0,0 });
    Matrix44_Decompose(srt, &scale, &rotation, &translation);
    Matrix4x4 s1 = Matrix44_TransformQuaternion(Matrix44_Identity(), q);
    Matrix4x4 s2 = Matrix44_Product(Matrix44_Identity(),Matrix44_CreateFromQuaternion(q));



    shutdown_log_system();
    return EXIT_SUCCESS;
}
