#ifndef SISD_DEFNS_DOT_H
#define SISD_DEFNS_DOT_H

#if defined(_MSC_VER)
/*! \def A byte aligned type */
#define ALIGNED_TYPE(t,x) __declspec(align(x)) t
#elif defined(__GNUC__) || defined(__MINGW32__)
/*! \def A byte aligned type */
#define ALIGNED_TYPE(t,x) t __attribute__((aligned(x)))
#endif

/*! \def A byte aligned class */
#define ALIGNED_CLASS(x) ALIGNED_TYPE(class, x)
/*! \def A byte aligned struct */
#define ALIGNED_STRUCT(x) ALIGNED_TYPE(struct, x)

#endif