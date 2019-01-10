#pragma once

using Microsoft::WRL::ComPtr;
using namespace DirectX;

class D3D12Instance
{
private:
	HRESULT hr = 0;
	HWND m_hWnd;
	UINT m_width, m_height;
	float m_aspectRatio;

	D3D12_VIEWPORT						m_viewport;
	D3D12_RECT							m_scissorRect;

	//流水线对象
	ComPtr<IDXGISwapChain4>				m_swapChain;
	ComPtr<IDXGIFactory6>				m_dxgiFactory;

	ComPtr<ID3D12Device>				m_device;
	ComPtr<ID3D12CommandQueue>			m_commandQueue;

	static const UINT FrameCount = 2U;
	ComPtr<ID3D12Resource>				m_renderTargets[FrameCount];
	ComPtr<ID3D12CommandAllocator>		m_commandAllocators[FrameCount];
	ComPtr<ID3D12GraphicsCommandList>	m_commandList;
	ComPtr<ID3D12DescriptorHeap>		m_rtvHeap;
	UINT								m_rtvDescriptorSize;

	// App resources.
	struct Vertex
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};
	ComPtr<ID3D12Resource>				m_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW			m_vertexBufferView;

	ComPtr<ID3D12RootSignature>			m_rootSignature;
	ComPtr<ID3D12PipelineState>			m_pipelineState;

	//同步对象
	UINT					m_frameIndex;
	HANDLE					m_fenceEvent;
	ComPtr<ID3D12Fence>		m_fence;
	UINT64					m_fenceValues[FrameCount];

private:
	void LoadPipeline();
	void LoadAssets();
	void PopulateCommandList();
	void MoveToNextFrame();
	void WaitForGpu();

public:
	D3D12Instance();
	virtual ~D3D12Instance();

	virtual void Initialize(HWND hWnd, UINT width, UINT height);
	virtual void OnUpdate();
	virtual void OnRender();
	virtual void OnDestroy();
};

