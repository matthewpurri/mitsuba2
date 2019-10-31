#include <mitsuba/python/python.h>
#include <mitsuba/render/emitter.h>

MTS_PY_EXPORT_CLASS_VARIANTS(Emitter) {
    using Base = typename Emitter::Base;
    MTS_PY_CLASS(Emitter, Base)
        .def_method(Emitter, is_environment)
        ;
}
