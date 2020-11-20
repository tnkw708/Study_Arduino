import sys

if len(sys.argv) != 2:
  print ("Please specify your file path")
  sys.exit()

filepath = sys.argv[1]

# ref: https://note.nkmk.me/python-print-basic/

### 入出力画像ファイルのオブジェクトを生成 ###
f  = open(filepath,"rb")

### BMPファイルヘッダ ###
bfType         = f.read(2)
bfSize         = f.read(4)
bfReserved1    = f.read(2)
bfReserved2    = f.read(2)
bfOffBitsbfOffBits = f.read(4)

### 情報ヘッダ ###
bcSize         = f.read(4)
bcWidth        = f.read(4)
bcHeight       = f.read(4)
bcPlanes       = f.read(2)
bcBitCount     = f.read(2)
biCompression  = f.read(4)
biSizeImage    = f.read(4)
biXPixPerMeter = f.read(4)
biYPixPerMeter = f.read(4)
biClrUsed      = f.read(4)
biCirImportant = f.read(4)

### 処理に必要そうなデータはデータとして持っておく ###
bfType_str             = bfType.decode()
bfOffBitsbfOffBits_int = int.from_bytes(bfOffBitsbfOffBits, "little")
bcSize_int             = int.from_bytes(bcSize,             "little")
bcWidth_int            = int.from_bytes(bcWidth,            "little")
bcHeight_int           = int.from_bytes(bcHeight,           "little")
bcBitCount_int         = int.from_bytes(bcBitCount,         "little")
biCompression_int      = int.from_bytes(biCompression,      "little")

### 想定する画像フォーマットでない場合は、ここで処理を終了 ###
if (bfType_str!="BM") or \
   (bcSize_int!=40)   or \
   (bcBitCount_int!=24) or \
   (biCompression_int!=0):
  print ("### This file format is not supported! Please use a valid bmp image ###")
  print ("bcSize=%d bcBitCount=%d bitCompression=%d" % (bcSize_int, bcBitCount_int, biCompression_int))
  sys.exit()

### 画像サイズ確認(デバッグ用) ###
# print ("(Width,Height)=(%d,%d)" % (bcWidth_int,bcHeight_int))

if (bcWidth_int != 16 or bcHeight_int != 16):
  print ("### This file size is wrong! Please prepare a 16x16 image ###")
  sys.exit()

### 画像データ本体へJump。ほどんど不要かも。###
offset = bfOffBitsbfOffBits_int-54
f.read(offset)

######################
### 画像データ処理 ###
######################

output = []

### 画像データ処理開始 ###
for y in range(bcHeight_int):
  line = []
  for x in range(bcWidth_int):
    B = int.from_bytes(f.read(1), "little")
    G = int.from_bytes(f.read(1), "little")
    R = int.from_bytes(f.read(1), "little")
    ### 画像処理 ###
    R = min(int(R/8), 32)
    G = min(int(G/8), 32)
    B = min(int(B/8), 32)
    line.append([R, G, B])
  if y % 2 == 1:
    output.extend(list(reversed(line)))
  else:
    output.extend(line)

print("{", end="")
for i in range(len(output)):
  print("{%d,%d,%d}" % (output[i][0], output[i][1], output[i][2]), end="")
  if(i != len(output)-1):
    print(",", end="")
print("}")   
        
### ファイルオブジェクトをclose ### 
f.close()