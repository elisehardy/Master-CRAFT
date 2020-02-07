

#ifndef MASTERCRAFT_IENTITY_HPP
#define MASTERCRAFT_IENTITY_HPP

#include <mastercraft/util/INonCopyable.hpp>
#include <GL/glew.h>

namespace mastercraft::entity {

    class IEntity : public util::INonCopyable {
    public:
        virtual ~IEntity() = default;

        virtual GLuint update() = 0;

        virtual GLuint render() = 0;
    };

}
#endif //MASTERCRAFT_IENTITY_HPP
