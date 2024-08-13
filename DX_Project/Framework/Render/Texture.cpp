#include "framework.h"

unordered_map<wstring, Texture*> Texture::texture_data;
// Ŭ�������� static���� ������ ��� ������ �ݵ�� .cpp ��򰡿��� �̷��� ���� ������ ����߸�
// ���������� ����� ������

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	: srv(srv), image(move(image))
	// move() : ScratchImage�� ��ü �ϳ��� �ִ� �����͸� �ٸ� ��ü�� �ű�� �� ����ϴ� �Լ�
{
}

Texture::~Texture()
{
	srv->Release();
}

Texture* Texture::Add(wstring file)
//�����ּҸ� �Է��ؼ� �̹� �Ҹ��� �ִ� �����̸� �װ� ���� ���� ��������� ��ü�� ��ȯ
//�ƴ϶�� ���� �� ������ �о�ͼ� �ν��Ͻ�ȭ

// static �Լ��̹Ƿ� Texture �ν��Ͻ��� �������� �ʾƵ� ��� ����
{
	if (texture_data.count(file) > 0) // �Է¹��� ������ �̹� �ʿ� ����Ǿ� �ִ� �����̶��
		return texture_data[file]; // �� ������ ���� ������ texture �ν��Ͻ��� �ּҸ� �ʿ��� ã�� ��ȯ

	// ���� ���ٸ�(=���� if���� ����ߴٸ�)
	// ���⼭���� ���������� �ν��Ͻ� ���� ������ ��ħ

	ScratchImage img;
	ID3D11ShaderResourceView* srv;
	// ������ �̾߱������� �� �Լ��� static �Լ�
	// ����, �� Ŭ������ �ν��Ͻ��� �������� �ʴ� ��Ȳ������ ������ �� �־�� �Ѵٴ� �ǹ�
	// �׷��� ������ �� �Լ� �ȿ����� �� Ŭ������ ������ �ִ� static�� �ƴ� ����� ����� �� ���
	// ����Ϸ��� ���⿡ ���� ������ �ؼ� ���� ������ �̿��ؾ� ��

	// ���ϴ� �ٸ� �������� �̿��߾��� ���� �ε� ����

	LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, img);
	// �� �Լ��� wstring�� �ν����� ���ϹǷ� LPCWSTR�� �ٲ���� ��
	CreateShaderResourceView(DEVICE, img.GetImages(), img.GetImageCount(), img.GetMetadata(), &srv);

	// �� ������ �̿��� ������� image�� srv�� �̿��� �� Texture �ν��Ͻ��� ����
	Texture* t = new Texture(srv, img);
	
	// �ν��Ͻ��� �ϼ������� �̸� �ʿ� ����
	texture_data[file] = t;
	// �̷��� ������ ���� �����ּҷ� Add�� ȣ������ ��� ���⿡ ����Ǿ� �ִ� �ν��Ͻ��� ��� ȣ��� ��

	return t;
}

void Texture::Delete()
{
	for (auto t : texture_data)
	{
		delete t.second;
	}
	texture_data.clear();
}

Vector2 Texture::GetSize()
// �� �ؽ���(=�̹��� ����)�� ������ �ִ� �������� ũ��(=���� ũ��)�� ��ȯ�ϴ� �Լ�
{
	return Vector2(image.GetMetadata().width, image.GetMetadata().height);
	// �ؽ����� ��Ÿ������(������ ���빰�� �ƴ� ���� ��ü�� ���� ������ ����ϴ� ������)�� �޾ƿͼ�
	// �� �� �ؽ�ó�� ���� ��ü ũ��/���� ��ü ũ�⸦ �̿��� �� �ؽ�ó�� ũ�⸦ Ȯ���Ͽ� ��ȯ

	// �̹������� ��ü�� ũ�⸦ �̿��ؾ� �� �� ����ϰ� �ǰ�,
	// ������ �츮�� �̰� �츮�� ����ϴ� ��ü �̹��� ��
	// �츮�� �̹��� ����ϰ��� �ϴ� ��������Ʈ�� ��ü �̹������� ��� ������ ������ ������ �ִ���
	// ����� �� �ַ� �ҷ��� ����ϰ� ��
}

void Texture::Set(UINT slot)
{
	DVC->PSSetShaderResources(slot, 1, &srv);
}
