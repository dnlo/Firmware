    /*This file is part of the Maslow Control Software.

    The Maslow Control Software is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Maslow Control Software is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the Maslow Control Software.  If not, see <http://www.gnu.org/licenses/>.
    
    Copyright 2014-2016 Bar Smith*/
    
    #ifndef Kinematics_h
    #define Kinematics_h
    
    #define ORIGINCHAINLEN   1650
    
    #include "Arduino.h"
    #include "BigNumber.h"
    #include "FormatDouble.h"

    class Kinematics{
        public:
            Kinematics();
            void  forward   (float chainALength, float chainBLength, float* X, float* Y);
            void  inverse   (float xTarget,float yTarget, float* aChainLength, float* bChainLength);
            void  oldInverse(float xTarget,float yTarget, float* aChainLength, float* bChainLength);
            void  test();
            void  speedTest(float input);
        private:
            BigNumber _float2BigNum (float value);
            float _moment(float Y1Plus, float Y2Plus, float Phi, float MSinPhi, float MSinPsi1, float MCosPsi1, float MSinPsi2, float MCosPsi2);
            float _YOffsetEqn(float YPlus, float Denominator, float Psi);
            void  _MatSolv();
            void  _MyTrig();
            //target router bit coordinates.
            float x = 2708.4;
            float y = 270;

            //utility variables
            float DegPerRad = 360/(4 * atan(1));
            unsigned long Time;
            boolean Mirror;

            //geometry
            float l = 310.0;                               //distance between sled attach points
            float s = 139.0;                               //vertical distance between sled attach points and bit
            float h = sqrt((l/2)*(l/2) + s * s);           //distance between sled attach point and bit
            float h3 = 79.0;                               //distance from bit to sled center of mass
            float D = 2978.4;                             //distance between sprocket centers
            float R = 10.2;                                //sprocket radius

            //Calculation tolerances
            float MaxError = 0.001;
            byte MaxTries = 10;
            float DeltaPhi = 0.001;
            float DeltaY = 0.01;

            //Criterion Computation Variables
            float Phi = -0.2;
            float TanGamma; 
            float TanLambda;
            float Y1Plus ;
            float Y2Plus;
            float Theta = atan(2*s/l);
            float Psi1 = Theta - Phi;
            float Psi2 = Theta + Phi;
            byte Tries = 0;
            float Jac[9];
            float Solution[3];
            float Crit[3];
            float Offsetx1;
            float Offsetx2;
            float Offsety1;
            float Offsety2;
            float SinPsi1;
            float CosPsi1;
            float SinPsi2;
            float CosPsi2;
            float SinPsi1D;
            float CosPsi1D;
            float SinPsi2D;
            float CosPsi2D;
            float MySinPhi;
            float MySinPhiDelta;

            //intermediate output
            float Lambda;
            float Gamma;

            // output = chain lengths measured from 12 o'clock

            float Chain1; //left chain length 
            float Chain2; //right chain length

            int i;
    };

    #endif