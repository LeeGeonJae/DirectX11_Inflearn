#pragma once
class VertexBuffer
{
public:
	VertexBuffer(ComPtr<ID3D11Device> device);
	~VertexBuffer();

	inline ComPtr<ID3D11Buffer> GetComPtr();
	inline uint32 GetStride();
	inline uint32 GetOffset();
	inline uint32 GetCount();

	template<typename T>
	void Create(const vector<T>& vertices)
	{
		_stride = sizeof(T);
		_count = static_cast<uint32>(vertices.size());

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = _stride * _count;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data();

		HRESULT hr = _device->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
		CHECK(hr);
	}

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;

private:

};

ComPtr<ID3D11Buffer> VertexBuffer::GetComPtr()
{
	return _vertexBuffer;
}

uint32 VertexBuffer::GetStride()
{
	return _stride;
}
uint32 VertexBuffer::GetOffset()
{
	return _offset;
}
uint32 VertexBuffer::GetCount()
{
	return _count;
}
