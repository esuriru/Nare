#pragma once
#include <Nare.h>

namespace Nare
{
    class Launcher2D : public Layer 
    {
    public:
        Launcher2D();
        virtual ~Launcher2D() = default;
        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(Timestep ts) override;
        void OnEvent(Event& event) override;
    private:
        Ref<Shader> _shader; 
        Ref<Texture> _texture;

        Ref<VertexArray> _squareVA;
    };

}