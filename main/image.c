#include "modm.h"
#include "ImageLayer.h"

void test()
{
	Sleep(100);
	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ

	Image images[1] =
	{
		{"image/test.bmp", 0, 0, 1} //{�̹��� �̸�, ���� x��ǥ, ���� y��ǥ, ũ�� ����(���� ������ �⺻���� 16�� ��)} 
	}; //�迭�� ù ���Ұ� ���� �Ʒ� �׷�����.

	imageLayer.imageCount = 1; //images �迭�� ũ�⺸�� �۰ų� ���ƾ� �Ѵ�.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}