#include "ImageLayer.h"
#include "modm.h"

void start()
{
	
	Sleep(10);

	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //초기화

	Image images[1] =
	{
		{"image/sample.png", 0, 0, 8} //{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
	}; //배열의 첫 원소가 가장 아래 그려진다.

	imageLayer.imageCount = 1; //images 배열의 크기보다 작거나 같아야 한다.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);

}

void first_Menu()
{
	
		Sleep(10);
		ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
		imageLayer.initialize(&imageLayer); //초기화

		Image images[4] =
		{
			 //{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
			{"image/menu-sample1.bmp", 100, 0},
			{"image/menu-sample2.bmp", 300, 300},
			{"image/menu-sample3.bmp", 600, 600}
		}; //배열의 첫 원소가 가장 아래 그려진다.

		imageLayer.imageCount = 4; //images 배열의 크기보다 작거나 같아야 한다.
		imageLayer.images = images;

		imageLayer.renderAll(&imageLayer);
	
}

void single_1()
{
	Sleep(10);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //초기화

	Image images[4] =
	{
		//{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
	   {"image/menu-sample1.bmp", 100, 0}
	}; //배열의 첫 원소가 가장 아래 그려진다.

	imageLayer.imageCount = 4; //images 배열의 크기보다 작거나 같아야 한다.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}

void single_2()
{
	Sleep(10);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //초기화

	Image images[4] =
	{
		//{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
	   {"image/menu-sample2.bmp", 300, 300}
	}; //배열의 첫 원소가 가장 아래 그려진다.

	imageLayer.imageCount = 4; //images 배열의 크기보다 작거나 같아야 한다.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}

void single_3()
{
	Sleep(10);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //초기화

	Image images[4] =
	{
		//{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
	   {"image/menu-sample3.bmp", 600, 600}
	}; //배열의 첫 원소가 가장 아래 그려진다.

	imageLayer.imageCount = 4; //images 배열의 크기보다 작거나 같아야 한다.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}

void t1()
{
	Sleep(10);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //초기화

	Image images[4] =
	{
		//{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
	   {"image/t1.bmp", 0, 0, 8}
	}; //배열의 첫 원소가 가장 아래 그려진다.

	imageLayer.imageCount = 4; //images 배열의 크기보다 작거나 같아야 한다.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}


void t2()
{
	Sleep(500);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //초기화

	Image images[4] =
	{
		//{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
	   {"image/t1.bmp", 0, 0, 8},
	   {"image/t2.bmp", 0, 0, 8},
	   {"image/t3.bmp", 0, 0, 8},
	   {"image/t4.bmp", 0, 0, 8}
	}; //배열의 첫 원소가 가장 아래 그려진다.

	imageLayer.imageCount = 4; //images 배열의 크기보다 작거나 같아야 한다.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}


void t3()
{
	Sleep(500);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //초기화

	Image images[4] =
	{
		//{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
	   {"image/t3.bmp", 0, 0, 8}
	}; //배열의 첫 원소가 가장 아래 그려진다.

	imageLayer.imageCount = 4; //images 배열의 크기보다 작거나 같아야 한다.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}


void t4()
{
	Sleep(500);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //초기화

	Image images[4] =
	{
		//{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
	   {"image/t4.bmp", 0, 0, 8}
	}; //배열의 첫 원소가 가장 아래 그려진다.

	imageLayer.imageCount = 4; //images 배열의 크기보다 작거나 같아야 한다.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}


void ttt()
{
	Sleep(500);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //초기화

	Image images[4] =
	{
		//{이미지 이름, 시작 x좌표, 시작 y좌표, 크기 배율(쓰지 않으면 기본값인 16이 들어감)} 
	   {"image/t1.bmp", 0, 0, 8}
	}; //배열의 첫 원소가 가장 아래 그려진다.

	imageLayer.imageCount = 4; //images 배열의 크기보다 작거나 같아야 한다.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}