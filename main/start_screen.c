#include "ImageLayer.h"
#include "modm.h"

void start()
{
	Sleep(500);

	ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
	imageLayer.initialize(&imageLayer); //�ʱ�ȭ

	Image images[1] =
	{
		{"image/sample.bmp", 0, 0, 0} //{�̹��� �̸�, ���� x��ǥ, ���� y��ǥ, ũ�� ����(���� ������ �⺻���� 16�� ��)} 
	}; //�迭�� ù ���Ұ� ���� �Ʒ� �׷�����.

	imageLayer.imageCount = 1; //images �迭�� ũ�⺸�� �۰ų� ���ƾ� �Ѵ�.
	imageLayer.images = images;

	imageLayer.renderAll(&imageLayer);
}
