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
 32;
 0.00631;0.09776;-0.61741;,
 -0.45597;0.09776;-0.51915;,
 -0.45597;-5.06749;-0.51915;,
 0.00631;-5.06749;-0.61741;,
 -0.83832;0.09776;-0.24136;,
 -0.83832;-5.06749;-0.24136;,
 -1.07464;0.09776;0.16794;,
 -1.07464;-5.06749;0.16794;,
 -1.12405;0.09776;0.63796;,
 -1.12405;-5.06749;0.63796;,
 -0.97798;0.09776;1.08744;,
 -0.97798;-5.06749;1.08744;,
 -0.66174;0.09776;1.43866;,
 -0.66174;-5.06749;1.43866;,
 -0.22999;0.09776;1.63089;,
 -0.22999;-5.06749;1.63089;,
 0.24261;0.09776;1.63089;,
 0.24261;-5.06749;1.63089;,
 0.67436;0.09776;1.43866;,
 0.67436;-5.06749;1.43866;,
 0.99061;0.09776;1.08744;,
 0.99061;-5.06749;1.08744;,
 1.13666;0.09776;0.63796;,
 1.13666;-5.06749;0.63796;,
 1.08725;0.09776;0.16794;,
 1.08725;-5.06749;0.16794;,
 0.85095;0.09776;-0.24136;,
 0.85095;-5.06749;-0.24136;,
 0.46859;0.09776;-0.51915;,
 0.46859;-5.06749;-0.51915;,
 0.00631;0.09776;-0.61741;,
 0.00631;-5.06749;-0.61741;;
 
 15;
 4;3,2,1,0;,
 4;2,5,4,1;,
 4;5,7,6,4;,
 4;7,9,8,6;,
 4;9,11,10,8;,
 4;11,13,12,10;,
 4;13,15,14,12;,
 4;15,17,16,14;,
 4;17,19,18,16;,
 4;19,21,20,18;,
 4;21,23,22,20;,
 4;23,25,24,22;,
 4;25,27,26,24;,
 4;27,29,28,26;,
 4;29,31,30,28;;
 
 MeshMaterialList {
  3;
  15;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.458400;0.749600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  15;
  -0.000000;0.000000;-1.000000;,
  -0.406733;0.000000;-0.913547;,
  -0.743136;0.000000;-0.669140;,
  -0.951051;0.000000;-0.309035;,
  -0.994520;0.000000;0.104544;,
  -0.866013;0.000000;0.500022;,
  -0.587787;0.000000;0.809016;,
  -0.207914;0.000000;0.978147;,
  0.207914;0.000000;0.978147;,
  0.587781;0.000000;0.809020;,
  0.866019;0.000000;0.500011;,
  0.994522;0.000000;0.104524;,
  0.951056;0.000000;-0.309018;,
  0.743144;0.000000;-0.669131;,
  0.406728;0.000000;-0.913549;;
  15;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,0,0,14;;
 }
 MeshTextureCoords {
  32;
  0.000000;0.000000;,
  0.066670;0.000000;,
  0.066670;1.000000;,
  0.000000;1.000000;,
  0.133330;0.000000;,
  0.133330;1.000000;,
  0.200000;0.000000;,
  0.200000;1.000000;,
  0.266670;0.000000;,
  0.266670;1.000000;,
  0.333330;0.000000;,
  0.333330;1.000000;,
  0.400000;0.000000;,
  0.400000;1.000000;,
  0.466670;0.000000;,
  0.466670;1.000000;,
  0.533330;0.000000;,
  0.533330;1.000000;,
  0.600000;0.000000;,
  0.600000;1.000000;,
  0.666670;0.000000;,
  0.666670;1.000000;,
  0.733330;0.000000;,
  0.733330;1.000000;,
  0.800000;0.000000;,
  0.800000;1.000000;,
  0.866670;0.000000;,
  0.866670;1.000000;,
  0.933330;0.000000;,
  0.933330;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;;
 }
}
