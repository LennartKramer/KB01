#include "RendererInterface.h"

RendererInterface::RendererInterface() { };

RendererInterface::~RendererInterface() { };

HRESULT RendererInterface::initD3D(HWND hWnd) { return 0; };

HRESULT RendererInterface::initGeometry(void) { return 0; };

void RendererInterface::cleanUp() { };

void RendererInterface::setupMatrices() { };

void RendererInterface::render() { };