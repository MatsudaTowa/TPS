xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 100;
 -85.11589;15.37350;85.11589;,
 -68.65125;19.27432;80.10337;,
 -68.65126;15.60461;68.65126;,
 -82.31349;17.30560;68.65125;,
 -45.76750;14.45023;83.63151;,
 -45.76750;14.09257;68.65125;,
 -46.55314;9.77267;46.55313;,
 -67.44837;13.19088;46.97038;,
 -86.12868;9.99548;47.11908;,
 0.00000;0.00000;91.53500;,
 0.00000;0.00000;68.65125;,
 -24.20529;3.69347;68.65125;,
 -23.39339;1.58268;90.77054;,
 0.00000;0.00000;45.76750;,
 -23.05456;0.38295;45.85291;,
 -45.45747;9.44820;-3.21133;,
 -45.76987;0.01031;22.88850;,
 -22.88375;0.00000;22.88375;,
 -21.20567;4.05439;2.73521;,
 9.32796;0.48814;20.19933;,
 -91.53500;0.00000;0.00000;,
 -91.53500;0.00000;22.88375;,
 -68.44730;0.91811;23.29165;,
 -68.25424;1.58593;-0.39768;,
 91.53500;0.00000;-91.53500;,
 45.76750;0.00000;-91.53500;,
 91.53500;0.00000;-45.76750;,
 45.76750;0.00000;-45.76750;,
 -91.53500;0.00000;-91.53500;,
 -91.53500;0.00000;-68.65125;,
 -68.49500;0.38875;-68.49547;,
 -68.65125;0.00000;-91.53500;,
 -91.53500;0.00000;-45.76750;,
 -66.25334;8.47946;-46.57264;,
 -46.76245;14.71557;-45.11236;,
 -45.76512;5.94444;-66.34027;,
 -45.76750;0.00000;-91.53500;,
 0.00000;0.00000;-91.53500;,
 -22.88375;0.00000;-91.53500;,
 -23.98300;4.76499;-66.45285;,
 0.00000;0.00000;-68.65125;,
 -24.68513;14.11667;-46.50190;,
 -1.20848;3.86128;-44.67775;,
 24.79987;10.98523;33.28712;,
 23.15128;1.34683;6.11164;,
 47.27651;3.12959;-1.14399;,
 28.60469;0.00000;-10.01164;,
 4.29070;0.00000;-4.29070;,
 22.88375;0.00000;-22.88375;,
 9.93300;0.18576;-28.63982;,
 -6.17277;7.83047;-24.34174;,
 17.16281;0.00000;-51.48843;,
 22.88375;0.00000;-68.65125;,
 34.32562;0.00000;-34.32562;,
 68.65125;0.00000;-22.88375;,
 -50.82433;16.63179;-22.89741;,
 -61.56315;13.77775;-34.33694;,
 -76.21693;4.66410;-33.87885;,
 -85.75451;0.15513;-22.88387;,
 -61.01261;9.43058;-11.44962;,
 -76.88938;1.54745;-11.59543;,
 -68.64767;8.96862;-22.89112;,
 -28.64611;14.30375;-11.74592;,
 -31.91864;18.38447;-28.61979;,
 -15.66292;14.46878;-33.65433;,
 -13.31932;6.84453;-8.25197;,
 -19.26718;14.92229;-21.44574;,
 -40.03942;17.87557;-15.99106;,
 -5.89972;0.00000;8.04507;,
 91.53500;0.00000;91.53500;,
 90.84983;1.49441;68.19447;,
 67.61616;10.92555;65.54600;,
 68.65125;0.00000;91.53500;,
 88.25853;7.54240;45.76750;,
 68.65126;15.99490;48.92700;,
 44.50559;16.40395;44.03238;,
 46.77551;12.19257;67.64324;,
 45.76750;0.06699;91.49772;,
 24.60749;10.24366;52.35031;,
 67.94667;3.00242;0.66935;,
 80.09312;0.00000;-11.44187;,
 91.53500;0.00000;0.00000;,
 51.48843;0.00000;-22.88375;,
 22.91698;6.60206;20.12296;,
 22.88375;0.00000;85.81406;,
 34.74409;4.38900;76.50034;,
 34.32562;12.35202;61.28648;,
 11.44187;0.00000;77.23265;,
 11.98033;1.49581;60.06984;,
 23.28378;4.16758;67.75119;,
 52.78442;16.94936;22.37461;,
 62.22292;20.22752;34.32562;,
 75.82653;15.55229;34.32562;,
 83.48413;8.15797;23.73100;,
 61.23189;10.87305;11.21592;,
 75.71410;6.97941;12.11679;,
 68.65125;15.24738;22.88375;,
 40.04656;0.00000;-16.44769;,
 60.06984;0.00000;-11.44187;,
 36.21073;12.78004;21.20968;;
 
 137;
 4;0,1,2,3;,
 4;4,5,2,1;,
 4;6,7,2,5;,
 4;8,3,2,7;,
 4;9,10,11,12;,
 4;13,14,11,10;,
 4;6,5,11,14;,
 4;4,12,11,5;,
 4;15,16,17,18;,
 4;6,14,17,16;,
 4;13,19,17,14;,
 4;20,21,22,23;,
 4;8,7,22,21;,
 4;6,16,22,7;,
 4;15,23,22,16;,
 3;24,25,26;,
 3;27,26,25;,
 4;28,29,30,31;,
 4;32,33,30,29;,
 4;34,35,30,33;,
 4;36,31,30,35;,
 4;37,38,39,40;,
 4;36,35,39,38;,
 4;34,41,39,35;,
 4;42,40,39,41;,
 3;19,13,43;,
 3;44,45,46;,
 3;44,46,47;,
 3;48,49,46;,
 3;50,47,49;,
 3;46,49,47;,
 4;37,40,51,52;,
 4;53,27,52,51;,
 4;40,42,49,51;,
 4;48,53,51,49;,
 3;27,25,52;,
 3;25,37,52;,
 3;26,27,54;,
 3;55,34,56;,
 3;34,33,56;,
 3;33,32,57;,
 3;32,58,57;,
 3;23,59,60;,
 3;55,61,59;,
 3;58,60,61;,
 3;59,61,60;,
 3;33,57,56;,
 3;58,61,57;,
 3;55,56,61;,
 3;57,61,56;,
 3;18,62,15;,
 3;34,55,63;,
 3;50,42,64;,
 3;42,41,64;,
 3;18,65,62;,
 3;50,66,65;,
 3;63,62,66;,
 3;65,66,62;,
 3;41,63,64;,
 3;50,64,66;,
 3;63,66,64;,
 3;44,47,19;,
 3;58,20,60;,
 3;20,23,60;,
 3;23,15,59;,
 3;15,55,59;,
 3;47,50,65;,
 3;49,42,50;,
 3;63,41,34;,
 3;62,63,67;,
 3;63,55,67;,
 3;55,15,67;,
 3;15,62,67;,
 4;47,65,68,19;,
 4;17,19,68,18;,
 3;65,18,68;,
 4;69,70,71,72;,
 4;73,74,71,70;,
 4;75,76,71,74;,
 4;77,72,71,76;,
 3;75,43,78;,
 3;43,13,78;,
 3;54,79,80;,
 3;79,81,80;,
 3;54,27,82;,
 3;27,53,82;,
 3;81,26,80;,
 3;26,54,80;,
 3;43,83,19;,
 3;19,83,44;,
 3;84,77,85;,
 3;77,76,85;,
 3;76,75,86;,
 3;75,78,86;,
 3;10,87,88;,
 3;84,89,87;,
 3;78,88,89;,
 3;87,89,88;,
 3;76,86,85;,
 3;78,89,86;,
 3;84,85,89;,
 3;86,89,85;,
 3;90,75,91;,
 3;75,74,91;,
 3;74,73,92;,
 3;73,93,92;,
 3;79,94,95;,
 3;90,96,94;,
 3;93,95,96;,
 3;94,96,95;,
 3;74,92,91;,
 3;93,96,92;,
 3;90,91,96;,
 3;92,96,91;,
 3;82,97,98;,
 3;46,97,48;,
 3;82,53,97;,
 3;53,48,97;,
 3;90,99,75;,
 3;83,43,99;,
 3;43,75,99;,
 3;83,99,44;,
 3;90,45,99;,
 3;45,44,99;,
 3;78,13,88;,
 3;13,10,88;,
 3;10,9,87;,
 3;9,84,87;,
 3;93,81,95;,
 3;81,79,95;,
 3;79,45,94;,
 3;45,90,94;,
 3;79,54,98;,
 3;54,82,98;,
 3;46,45,97;,
 3;79,98,45;,
 3;98,97,45;;
 
 MeshMaterialList {
  1;
  137;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\soil.jpg";
   }
  }
 }
 MeshNormals {
  95;
  -0.046065;0.992225;-0.115617;,
  0.162168;0.962859;0.215882;,
  -0.008378;0.999930;-0.008378;,
  0.000000;1.000000;0.000000;,
  0.036416;0.999227;0.014792;,
  0.115089;0.974551;-0.192366;,
  0.029663;0.999120;-0.029663;,
  -0.081751;0.996575;0.012475;,
  0.140593;0.988369;0.057965;,
  0.303875;0.949887;-0.073313;,
  -0.228637;0.973411;0.014039;,
  -0.111477;0.904539;0.411560;,
  -0.056930;0.949348;-0.309026;,
  0.476944;0.872424;0.106779;,
  -0.061976;0.933263;-0.353807;,
  -0.095237;0.912523;0.397783;,
  -0.279946;0.959938;-0.012189;,
  0.382173;0.912766;-0.144229;,
  -0.040674;0.985356;-0.165589;,
  0.193931;0.953252;-0.231735;,
  -0.172292;0.982009;0.077286;,
  -0.123059;0.959857;-0.252054;,
  0.046175;0.988862;-0.141490;,
  0.280300;0.953169;-0.113580;,
  0.020162;0.953717;-0.300030;,
  -0.033388;0.986875;-0.157996;,
  0.001025;0.999924;0.012328;,
  0.166460;0.980556;-0.103925;,
  0.288685;0.956828;0.033792;,
  0.129646;0.929303;0.345815;,
  0.052751;0.997727;-0.041934;,
  -0.162778;0.983707;-0.076314;,
  -0.074839;0.975913;-0.204922;,
  -0.185430;0.960152;0.209105;,
  0.045557;0.986259;-0.158803;,
  0.266836;0.962951;-0.039040;,
  0.081960;0.995642;0.044483;,
  -0.047479;0.984864;-0.166700;,
  -0.199834;0.952299;-0.230637;,
  0.006436;0.999976;-0.002379;,
  0.464910;0.879505;0.101634;,
  0.144372;0.984365;-0.100908;,
  0.075685;0.950273;-0.302082;,
  -0.088896;0.992686;-0.081682;,
  -0.306929;0.933019;-0.187802;,
  -0.071728;0.958969;-0.274286;,
  -0.057769;0.996186;-0.065393;,
  0.057417;0.987197;-0.148811;,
  0.185703;0.943020;-0.276095;,
  -0.363418;0.925480;-0.106835;,
  -0.349236;0.934582;0.067756;,
  -0.250786;0.958787;0.133541;,
  0.087208;0.996107;-0.012854;,
  0.001574;0.999999;-0.000315;,
  -0.128931;0.978545;-0.160707;,
  0.108981;0.963434;-0.244782;,
  0.183605;0.982998;-0.001792;,
  -0.033382;0.997543;-0.061591;,
  0.049686;0.998702;-0.011203;,
  -0.008535;0.999075;-0.042158;,
  -0.380690;0.921169;-0.080759;,
  -0.438542;0.898664;-0.009122;,
  -0.339934;0.880807;0.329581;,
  -0.442830;0.885048;0.143495;,
  -0.305913;0.936218;0.172954;,
  0.190109;0.898067;0.396654;,
  0.390923;0.917958;-0.067319;,
  0.294892;0.909091;0.294265;,
  0.351322;0.913485;0.205228;,
  -0.046748;0.953371;0.298157;,
  0.120878;0.975549;0.183556;,
  0.274738;0.932711;0.233600;,
  0.226532;0.948375;0.221963;,
  -0.094718;0.931707;0.350642;,
  0.105950;0.941623;0.319562;,
  -0.377042;0.910691;0.168762;,
  -0.109514;0.974828;0.194207;,
  0.426112;0.867493;-0.256678;,
  -0.083594;0.944308;-0.318267;,
  -0.389689;0.875855;-0.284641;,
  0.061189;0.996249;-0.061189;,
  0.159224;0.945548;0.283877;,
  -0.220210;0.898621;0.379458;,
  -0.281591;0.913242;0.294439;,
  -0.101824;0.991876;0.076253;,
  -0.311080;0.913608;0.261819;,
  -0.266399;0.952140;0.149869;,
  0.096913;0.994297;-0.044512;,
  0.427843;0.901513;-0.064995;,
  0.129147;0.862110;-0.489988;,
  0.276519;0.892694;-0.355858;,
  0.254916;0.883487;-0.393025;,
  -0.017742;0.992151;-0.123781;,
  -0.005525;0.997909;-0.064405;,
  -0.276034;0.919635;-0.279421;;
  137;
  4;0,22,34,25;,
  4;9,23,34,22;,
  4;19,24,34,23;,
  4;12,25,34,24;,
  4;4,26,35,28;,
  4;10,27,35,26;,
  4;19,23,35,27;,
  4;9,28,35,23;,
  4;11,30,36,29;,
  4;19,27,36,30;,
  4;10,31,36,27;,
  4;7,32,37,33;,
  4;12,24,37,32;,
  4;19,30,37,24;,
  4;11,33,37,30;,
  3;3,3,3;,
  3;3,3,3;,
  4;2,43,54,46;,
  4;16,44,54,43;,
  4;21,45,54,44;,
  4;18,46,54,45;,
  4;6,47,55,41;,
  4;18,45,55,47;,
  4;21,48,55,45;,
  4;17,41,55,48;,
  3;31,10,49;,
  3;38,14,57;,
  3;38,57,8;,
  3;39,56,57;,
  3;40,8,56;,
  3;57,56,8;,
  4;6,41,58,3;,
  4;53,3,3,58;,
  4;41,17,56,58;,
  4;39,53,58,56;,
  3;3,3,3;,
  3;3,6,3;,
  3;3,3,59;,
  3;51,21,60;,
  3;21,44,60;,
  3;44,16,61;,
  3;16,50,61;,
  3;33,62,64;,
  3;51,63,62;,
  3;50,64,63;,
  3;62,63,64;,
  3;44,61,60;,
  3;50,63,61;,
  3;51,60,63;,
  3;61,63,60;,
  3;29,65,11;,
  3;21,51,52;,
  3;40,17,66;,
  3;17,48,66;,
  3;29,67,65;,
  3;40,68,67;,
  3;52,65,68;,
  3;67,68,65;,
  3;48,52,66;,
  3;40,66,68;,
  3;52,68,66;,
  3;38,8,31;,
  3;50,7,64;,
  3;7,33,64;,
  3;33,11,62;,
  3;11,51,62;,
  3;8,40,67;,
  3;56,17,40;,
  3;52,48,21;,
  3;65,52,69;,
  3;52,51,69;,
  3;51,11,69;,
  3;11,65,69;,
  4;8,67,70,31;,
  4;36,31,70,29;,
  3;67,29,70;,
  4;1,71,81,74;,
  4;13,72,81,71;,
  4;20,73,81,72;,
  4;15,74,81,73;,
  3;20,49,75;,
  3;49,10,75;,
  3;59,42,80;,
  3;42,5,80;,
  3;59,3,3;,
  3;3,53,3;,
  3;5,3,80;,
  3;3,59,80;,
  3;49,79,31;,
  3;31,79,38;,
  3;76,15,82;,
  3;15,73,82;,
  3;73,20,83;,
  3;20,75,83;,
  3;26,84,86;,
  3;76,85,84;,
  3;75,86,85;,
  3;84,85,86;,
  3;73,83,82;,
  3;75,85,83;,
  3;76,82,85;,
  3;83,85,82;,
  3;78,20,87;,
  3;20,72,87;,
  3;72,13,88;,
  3;13,77,88;,
  3;42,89,91;,
  3;78,90,89;,
  3;77,91,90;,
  3;89,90,91;,
  3;72,88,87;,
  3;77,90,88;,
  3;78,87,90;,
  3;88,90,87;,
  3;3,93,92;,
  3;57,93,39;,
  3;3,53,93;,
  3;53,39,93;,
  3;78,94,20;,
  3;79,49,94;,
  3;49,20,94;,
  3;79,94,38;,
  3;78,14,94;,
  3;14,38,94;,
  3;75,10,86;,
  3;10,26,86;,
  3;26,4,84;,
  3;4,76,84;,
  3;77,5,91;,
  3;5,42,91;,
  3;42,14,89;,
  3;14,78,89;,
  3;42,59,92;,
  3;59,3,92;,
  3;57,14,93;,
  3;42,92,14;,
  3;92,93,14;;
 }
}