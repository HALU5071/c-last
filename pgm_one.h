/***********************************************************/
/*                         定数宣言                        */
/***********************************************************/
#define MAX_IMAGESIZE   1024 //縦・横の最大画素数
#define MAX_BRIGHTNESS   255 //最大階調値
#define GRAYLEVEL        256 //想定する階調値（最大諧調値＋１）
#define MAX_FILENAME     256 //ファイル名最大長
#define MAX_BUFFERSIZE   256 //バッファ最大長


/***********************************************************/
/*                   グローバル変数宣言                    */
/***********************************************************/
unsigned char image1[MAX_IMAGESIZE][MAX_IMAGESIZE]; //入力画像用配列
int x_size1, y_size1;                               //image1の横画素数，縦画素数

/***********************************************************/
/*                   関数プロトタイプ宣言                  */
/***********************************************************/
void load_image_data(char *file_name); //画像読み込み用関数


/***********************************************************/
/*                           関数                          */
/***********************************************************/
//-----------------------------------------------------------------------------
/**
 *pgm画像，横画素数，縦画素数のデータをファイルから読み込み
 *image1[][], x_size1, y_size1 にそれぞれ代入する関数
 */
void load_image_data(char *file_name){

	char buffer[MAX_BUFFERSIZE];  //データ読み込み用作業変数
	FILE *fp;                     //ファイルポインタ
	int max_gray;                 //最大諧調値
	int x, y;                     //ループ変数

	printf("%s を処理します\n", file_name);

	/***** 入力ファイルのオープン *****/
	fp = fopen(file_name,"rb");
	if(NULL == fp){//fpがNULLなら入力失敗

		printf( "その名前のファイルは存在しません\n" );
		exit(1);

	}

	/***** ファイルタイプ（P5）の確認 *****/
	fgets(buffer,MAX_BUFFERSIZE,fp);
	if(buffer[0] != 'P' || buffer[1] != '5'){

		printf("ファイルのフォーマットがP5とは異なります\n" );
		exit(1);

	}

	/***** x_size1, y_size1 の代入 *****/
	x_size1 = 0; //x_size1の初期化
	y_size1 = 0; //y_size1の初期化
	while(x_size1 == 0 || y_size1 == 0){

		fgets(buffer,MAX_BUFFERSIZE,fp);
		if(buffer[0] != '#')//#から始まるコメントは読み飛ばす
			sscanf(buffer,"%d %d",&x_size1,&y_size1);

	}

	/***** max_gray の代入 *****/
	max_gray = 0; //max_grayの初期化
	while( max_gray == 0 ){

		fgets(buffer,MAX_BUFFERSIZE,fp);
		if(buffer[0] != '#')//#から始まるコメントは読み飛ばす
			sscanf(buffer,"%d",&max_gray);
	}

	/***** 読込む画像が適切かチェック *****/
	if(x_size1 > MAX_IMAGESIZE || y_size1 > MAX_IMAGESIZE){//画像の大きさが想定値以内か調べる

		printf("想定値 %d × %d を超えています\n",MAX_IMAGESIZE,MAX_IMAGESIZE);
		printf("もう少し小さい画像を使ってください\n" );
		exit(1);

	}
	if( max_gray != MAX_BRIGHTNESS){//最大諧調値が適切か調べる
		printf( "最大諧調値が不適切です\n" );
		exit(1);
	}

	/***** 画像データを読み込んで，画像用配列に代入する *****/
	for(y = 0;y < y_size1;y++)
		for( x= 0;x < x_size1;x++)
			image1[y][x] = (unsigned char)fgetc(fp);

	fclose(fp);

}
