#pragma once
class IndexBuffer
{
public:
	IndexBuffer(ComPtr<ID3D11Device> device);
	~IndexBuffer();

	inline ComPtr<ID3D11Buffer> GetComPtr();
	inline uint32 GetStride();
	inline uint32 GetOffset();
	inline uint32 GetCount();

	void Create(const vector<uint32>& indices);

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;
};

ComPtr<ID3D11Buffer> IndexBuffer::GetComPtr()
{
	return _indexBuffer;
}

uint32 IndexBuffer::GetStride()
{
	return _stride;
}
uint32 IndexBuffer::GetOffset()
{
	return _offset;
}
uint32 IndexBuffer::GetCount()
{
	return _count;
}


