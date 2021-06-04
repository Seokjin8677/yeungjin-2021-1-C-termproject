#include "ImageLayer.h"
#include "modm.h"

void start()
{
	

	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ

	Image images[1] =
	{
		{"image/sample.png", 0, 0, 8} //{�̹��� �̸�, ���� x��ǥ, ���� y��ǥ, ũ�� ����(���� ������ �⺻���� 16�� ��)} 
	}; //�迭�� ù ���Ұ� ���� �Ʒ� �׷�����.

	imageLayer.imageCount = 1; //images �迭�� ũ�⺸�� �۰ų� ���ƾ� �Ѵ�.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);

}

void first_Menu()
{
	
		Sleep(10);
		ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
		imageLayer.initialize(&imageLayer); //�ʱ�ȭ

		Image images[4] =
		{
			 //{�̹��� �̸�, ���� x��ǥ, ���� y��ǥ, ũ�� ����(���� ������ �⺻���� 16�� ��)} 
			{"image/menu-sample1.bmp", 100, 0},
			{"image/menu-sample2.bmp", 300, 300},
			{"image/menu-sample3.bmp", 600, 600}
		}; //�迭�� ù ���Ұ� ���� �Ʒ� �׷�����.

		imageLayer.imageCount = 4; //images �迭�� ũ�⺸�� �۰ų� ���ƾ� �Ѵ�.
		imageLayer.images = images;

		imageLayer.renderAll(&imageLayer);
	
}

void single_1()
{
	Sleep(10);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ

	Image images[4] =
	{
		//{�̹��� �̸�, ���� x��ǥ, ���� y��ǥ, ũ�� ����(���� ������ �⺻���� 16�� ��)} 
	   {"image/menu-sample1.bmp", 100, 0}
	}; //�迭�� ù ���Ұ� ���� �Ʒ� �׷�����.

	imageLayer.imageCount = 4; //images �迭�� ũ�⺸�� �۰ų� ���ƾ� �Ѵ�.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}

void single_2()
{
	Sleep(10);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ

	Image images[4] =
	{
		//{�̹��� �̸�, ���� x��ǥ, ���� y��ǥ, ũ�� ����(���� ������ �⺻���� 16�� ��)} 
	   {"image/menu-sample2.bmp", 300, 300}
	}; //�迭�� ù ���Ұ� ���� �Ʒ� �׷�����.

	imageLayer.imageCount = 4; //images �迭�� ũ�⺸�� �۰ų� ���ƾ� �Ѵ�.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}

void single_3()
{
	Sleep(10);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ

	Image images[4] =
	{
		//{�̹��� �̸�, ���� x��ǥ, ���� y��ǥ, ũ�� ����(���� ������ �⺻���� 16�� ��)} 
	   {"image/menu-sample3.bmp", 600, 600}
	}; //�迭�� ù ���Ұ� ���� �Ʒ� �׷�����.

	imageLayer.imageCount = 4; //images �迭�� ũ�⺸�� �۰ų� ���ƾ� �Ѵ�.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}