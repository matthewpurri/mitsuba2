#include <mitsuba/core/ddistr.h>
#include <mitsuba/python/python.h>

MTS_PY_EXPORT(DiscreteDistribution) {
    MTS_PY_STRUCT(DiscreteDistribution)
        .def(py::init<size_t>(), py::arg("n_entries") = 0,
             D(DiscreteDistribution, DiscreteDistribution))
        .def(py::init([](py::array_t<Float> data) {
            if (data.ndim() != 1)
                throw std::domain_error("array has incorrect dimension");
            return DiscreteDistribution(
                (size_t) data.shape(0),
                data.data()
            );
        }))
        .def_method(DiscreteDistribution, clear)
        .def_method(DiscreteDistribution, reserve)
        .def_method(DiscreteDistribution, append)
        .def_method(DiscreteDistribution, size)

        .def("eval", [](const DiscreteDistribution &d, size_t i) {
            return d.eval(i);
        }, D(DiscreteDistribution, eval), "index"_a)

        .def("eval", vectorize_wrapper(
            [](const DiscreteDistribution &d, SizeP i, mask_t<SizeP> active) {
                return d.eval(i, active);
            }
        ), D(DiscreteDistribution, eval), "i"_a, "active"_a = true)

        .def_method(DiscreteDistribution, normalized)
        .def_method(DiscreteDistribution, sum)
        .def_method(DiscreteDistribution, normalization)
        .def_method(DiscreteDistribution, cdf)
        .def_method(DiscreteDistribution, normalize)

        // ---------------------------------------------------------------------

        .def("sample", [](const DiscreteDistribution &d, Float arg) { return d.sample(arg); },
             "sample_value"_a, D(DiscreteDistribution, sample))
        .def("sample", vectorize_wrapper(&DiscreteDistribution::sample<FloatP>),
             "sample_value"_a, "active"_a = true)

        // ---------------------------------------------------------------------

        .def("sample_pdf", [](const DiscreteDistribution &d, Float arg) { return d.sample_pdf(arg); },
             "sample_value"_a, D(DiscreteDistribution, sample_pdf))
        .def("sample_pdf", vectorize_wrapper(&DiscreteDistribution::sample_pdf<FloatP>),
             "sample_value"_a, "active"_a = true)

        // ---------------------------------------------------------------------

        .def("sample_reuse", [](const DiscreteDistribution &d, Float arg) { return d.sample_reuse(arg); },
             "sample_value"_a, D(DiscreteDistribution, sample_reuse))
        .def("sample_reuse", vectorize_wrapper(&DiscreteDistribution::sample_reuse<FloatP>),
             "sample_value"_a, "active"_a = true)

        // ---------------------------------------------------------------------

        .def("sample_reuse_pdf", [](const DiscreteDistribution &d, Float arg) { return d.sample_reuse_pdf(arg); },
             "sample_value"_a, D(DiscreteDistribution, sample_reuse_pdf))
        .def("sample_reuse_pdf", vectorize_wrapper(&DiscreteDistribution::sample_reuse_pdf<FloatP>),
             "sample_value"_a, "active"_a = true)

        // ---------------------------------------------------------------------

        .def_repr(DiscreteDistribution);
}
