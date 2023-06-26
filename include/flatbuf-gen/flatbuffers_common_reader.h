#ifndef FLATBUFFERS_COMMON_READER_H
#define FLATBUFFERS_COMMON_READER_H

/* Generated by flatcc 0.6.2 FlatBuffers schema compiler for C by dvide.com */

/* Common FlatBuffers read functionality for C. */

#include "flatcc/flatcc_prologue.h"
#include "flatcc/flatcc_flatbuffers.h"


#define __flatbuffers_read_scalar_at_byteoffset(N, p, o) N ## _read_from_pe((uint8_t *)(p) + (o))
#define __flatbuffers_read_scalar(N, p) N ## _read_from_pe(p)
#define __flatbuffers_read_vt(ID, offset, t)\
flatbuffers_voffset_t offset = 0;\
{   flatbuffers_voffset_t id__tmp, *vt__tmp;\
    FLATCC_ASSERT(t != 0 && "null pointer table access");\
    id__tmp = ID;\
    vt__tmp = (flatbuffers_voffset_t *)((uint8_t *)(t) -\
        __flatbuffers_soffset_read_from_pe(t));\
    if (__flatbuffers_voffset_read_from_pe(vt__tmp) >= sizeof(vt__tmp[0]) * (id__tmp + 3u)) {\
        offset = __flatbuffers_voffset_read_from_pe(vt__tmp + id__tmp + 2);\
    }\
}
#define __flatbuffers_field_present(ID, t) { __flatbuffers_read_vt(ID, offset__tmp, t) return offset__tmp != 0; }
#define __flatbuffers_scalar_field(T, ID, t)\
{\
    __flatbuffers_read_vt(ID, offset__tmp, t)\
    if (offset__tmp) {\
        return (const T *)((uint8_t *)(t) + offset__tmp);\
    }\
    return 0;\
}
#define __flatbuffers_define_scalar_field(ID, N, NK, TK, T, V)\
static inline T N ## _ ## NK ## _get(N ## _table_t t__tmp)\
{ __flatbuffers_read_vt(ID, offset__tmp, t__tmp)\
  return offset__tmp ? __flatbuffers_read_scalar_at_byteoffset(TK, t__tmp, offset__tmp) : V;\
}\
static inline const T *N ## _ ## NK ## _get_ptr(N ## _table_t t__tmp)\
__flatbuffers_scalar_field(T, ID, t__tmp)\
static inline int N ## _ ## NK ## _is_present(N ## _table_t t__tmp)\
__flatbuffers_field_present(ID, t__tmp)\
__flatbuffers_define_scan_by_scalar_field(N, NK, T)
#define __flatbuffers_define_scalar_optional_field(ID, N, NK, TK, T, V)\
__flatbuffers_define_scalar_field(ID, N, NK, TK, T, V)\
static inline TK ## _option_t N ## _ ## NK ## _option(N ## _table_t t__tmp)\
{ TK ## _option_t ret; __flatbuffers_read_vt(ID, offset__tmp, t__tmp)\
  ret.is_null = offset__tmp == 0; ret.value = offset__tmp ?\
  __flatbuffers_read_scalar_at_byteoffset(TK, t__tmp, offset__tmp) : V;\
  return ret; }
#define __flatbuffers_struct_field(T, ID, t, r)\
{\
    __flatbuffers_read_vt(ID, offset__tmp, t)\
    if (offset__tmp) {\
        return (T)((uint8_t *)(t) + offset__tmp);\
    }\
    FLATCC_ASSERT(!(r) && "required field missing");\
    return 0;\
}
#define __flatbuffers_offset_field(T, ID, t, r, adjust)\
{\
    flatbuffers_uoffset_t *elem__tmp;\
    __flatbuffers_read_vt(ID, offset__tmp, t)\
    if (offset__tmp) {\
        elem__tmp = (flatbuffers_uoffset_t *)((uint8_t *)(t) + offset__tmp);\
        /* Add sizeof so C api can have raw access past header field. */\
        return (T)((uint8_t *)(elem__tmp) + adjust +\
              __flatbuffers_uoffset_read_from_pe(elem__tmp));\
    }\
    FLATCC_ASSERT(!(r) && "required field missing");\
    return 0;\
}
#define __flatbuffers_vector_field(T, ID, t, r) __flatbuffers_offset_field(T, ID, t, r, sizeof(flatbuffers_uoffset_t))
#define __flatbuffers_table_field(T, ID, t, r) __flatbuffers_offset_field(T, ID, t, r, 0)
#define __flatbuffers_define_struct_field(ID, N, NK, T, r)\
static inline T N ## _ ## NK ## _get(N ## _table_t t__tmp)\
__flatbuffers_struct_field(T, ID, t__tmp, r)\
static inline int N ## _ ## NK ## _is_present(N ## _table_t t__tmp)\
__flatbuffers_field_present(ID, t__tmp)
#define __flatbuffers_define_vector_field(ID, N, NK, T, r)\
static inline T N ## _ ## NK ## _get(N ## _table_t t__tmp)\
__flatbuffers_vector_field(T, ID, t__tmp, r)\
static inline int N ## _ ## NK ## _is_present(N ## _table_t t__tmp)\
__flatbuffers_field_present(ID, t__tmp)
#define __flatbuffers_define_table_field(ID, N, NK, T, r)\
static inline T N ## _ ## NK ## _get(N ## _table_t t__tmp)\
__flatbuffers_table_field(T, ID, t__tmp, r)\
static inline int N ## _ ## NK ## _is_present(N ## _table_t t__tmp)\
__flatbuffers_field_present(ID, t__tmp)
#define __flatbuffers_define_string_field(ID, N, NK, r)\
static inline flatbuffers_string_t N ## _ ## NK ## _get(N ## _table_t t__tmp)\
__flatbuffers_vector_field(flatbuffers_string_t, ID, t__tmp, r)\
static inline int N ## _ ## NK ## _is_present(N ## _table_t t__tmp)\
__flatbuffers_field_present(ID, t__tmp)\
__flatbuffers_define_scan_by_string_field(N, NK)
#define __flatbuffers_vec_len(vec)\
{ return (vec) ? (size_t)__flatbuffers_uoffset_read_from_pe((flatbuffers_uoffset_t *)vec - 1) : 0; }
#define __flatbuffers_string_len(s) __flatbuffers_vec_len(s)
static inline size_t flatbuffers_vec_len(const void *vec)
__flatbuffers_vec_len(vec)
#define __flatbuffers_scalar_vec_at(N, vec, i)\
{ FLATCC_ASSERT(flatbuffers_vec_len(vec) > (i) && "index out of range");\
  return __flatbuffers_read_scalar(N, &(vec)[i]); }
#define __flatbuffers_struct_vec_at(vec, i)\
{ FLATCC_ASSERT(flatbuffers_vec_len(vec) > (i) && "index out of range"); return (vec) + (i); }
/* `adjust` skips past the header for string vectors. */
#define __flatbuffers_offset_vec_at(T, vec, i, adjust)\
{ const flatbuffers_uoffset_t *elem__tmp = (vec) + (i);\
  FLATCC_ASSERT(flatbuffers_vec_len(vec) > (i) && "index out of range");\
  return (T)((uint8_t *)(elem__tmp) + (size_t)__flatbuffers_uoffset_read_from_pe(elem__tmp) + (adjust)); }
#define __flatbuffers_define_scalar_vec_len(N)\
static inline size_t N ## _vec_len(N ##_vec_t vec__tmp)\
{ return flatbuffers_vec_len(vec__tmp); }
#define __flatbuffers_define_scalar_vec_at(N, T) \
static inline T N ## _vec_at(N ## _vec_t vec__tmp, size_t i__tmp)\
__flatbuffers_scalar_vec_at(N, vec__tmp, i__tmp)
typedef const char *flatbuffers_string_t;
static inline size_t flatbuffers_string_len(flatbuffers_string_t s)
__flatbuffers_string_len(s)
typedef const flatbuffers_uoffset_t *flatbuffers_string_vec_t;
typedef flatbuffers_uoffset_t *flatbuffers_string_mutable_vec_t;
static inline size_t flatbuffers_string_vec_len(flatbuffers_string_vec_t vec)
__flatbuffers_vec_len(vec)
static inline flatbuffers_string_t flatbuffers_string_vec_at(flatbuffers_string_vec_t vec, size_t i)
__flatbuffers_offset_vec_at(flatbuffers_string_t, vec, i, sizeof(vec[0]))
typedef const void *flatbuffers_generic_t;
typedef void *flatbuffers_mutable_generic_t;
static inline flatbuffers_string_t flatbuffers_string_cast_from_generic(const flatbuffers_generic_t p)
{ return p ? ((const char *)p) + __flatbuffers_uoffset__size() : 0; }
typedef const flatbuffers_uoffset_t *flatbuffers_generic_vec_t;
typedef flatbuffers_uoffset_t *flatbuffers_generic_table_mutable_vec_t;
static inline size_t flatbuffers_generic_vec_len(flatbuffers_generic_vec_t vec)
__flatbuffers_vec_len(vec)
static inline flatbuffers_generic_t flatbuffers_generic_vec_at(flatbuffers_generic_vec_t vec, size_t i)
__flatbuffers_offset_vec_at(flatbuffers_generic_t, vec, i, 0)
static inline flatbuffers_generic_t flatbuffers_generic_vec_at_as_string(flatbuffers_generic_vec_t vec, size_t i)
__flatbuffers_offset_vec_at(flatbuffers_generic_t, vec, i, sizeof(vec[0]))
typedef struct flatbuffers_union {
    flatbuffers_union_type_t type;
    flatbuffers_generic_t value;
} flatbuffers_union_t;
typedef struct flatbuffers_union_vec {
    const flatbuffers_union_type_t *type;
    const flatbuffers_uoffset_t *value;
} flatbuffers_union_vec_t;
typedef struct flatbuffers_mutable_union {
    flatbuffers_union_type_t type;
    flatbuffers_mutable_generic_t value;
} flatbuffers_mutable_union_t;
typedef struct flatbuffers_mutable_union_vec {
    flatbuffers_union_type_t *type;
    flatbuffers_uoffset_t *value;
} flatbuffers_mutable_union_vec_t;
static inline flatbuffers_mutable_union_t flatbuffers_mutable_union_cast(flatbuffers_union_t u__tmp)\
{ flatbuffers_mutable_union_t mu = { u__tmp.type, (flatbuffers_mutable_generic_t)u__tmp.value };\
  return mu; }
static inline flatbuffers_mutable_union_vec_t flatbuffers_mutable_union_vec_cast(flatbuffers_union_vec_t uv__tmp)\
{ flatbuffers_mutable_union_vec_t muv =\
  { (flatbuffers_union_type_t *)uv__tmp.type, (flatbuffers_uoffset_t *)uv__tmp.value }; return muv; }
#define __flatbuffers_union_type_field(ID, t)\
{\
    __flatbuffers_read_vt(ID, offset__tmp, t)\
    return offset__tmp ? __flatbuffers_read_scalar_at_byteoffset(__flatbuffers_utype, t, offset__tmp) : 0;\
}
static inline flatbuffers_string_t flatbuffers_string_cast_from_union(const flatbuffers_union_t u__tmp)\
{ return flatbuffers_string_cast_from_generic(u__tmp.value); }
#define __flatbuffers_define_union_field(NS, ID, N, NK, T, r)\
static inline T ## _union_type_t N ## _ ## NK ## _type_get(N ## _table_t t__tmp)\
__## NS ## union_type_field(((ID) - 1), t__tmp)\
static inline NS ## generic_t N ## _ ## NK ## _get(N ## _table_t t__tmp)\
__## NS ## table_field(NS ## generic_t, ID, t__tmp, r)\
static inline int N ## _ ## NK ## _is_present(N ## _table_t t__tmp)\
__## NS ## field_present(ID, t__tmp)\
static inline T ## _union_t N ## _ ## NK ## _union(N ## _table_t t__tmp)\
{ T ## _union_t u__tmp = { 0, 0 }; u__tmp.type = N ## _ ## NK ## _type_get(t__tmp);\
  if (u__tmp.type == 0) return u__tmp; u__tmp.value = N ## _ ## NK ## _get(t__tmp); return u__tmp; }\
static inline NS ## string_t N ## _ ## NK ## _as_string(N ## _table_t t__tmp)\
{ return NS ## string_cast_from_generic(N ## _ ## NK ## _get(t__tmp)); }\

#define __flatbuffers_define_union_vector_ops(NS, T)\
static inline size_t T ## _union_vec_len(T ## _union_vec_t uv__tmp)\
{ return NS ## vec_len(uv__tmp.type); }\
static inline T ## _union_t T ## _union_vec_at(T ## _union_vec_t uv__tmp, size_t i__tmp)\
{ T ## _union_t u__tmp = { 0, 0 }; size_t n__tmp = NS ## vec_len(uv__tmp.type);\
  FLATCC_ASSERT(n__tmp > (i__tmp) && "index out of range"); u__tmp.type = uv__tmp.type[i__tmp];\
  /* Unknown type is treated as NONE for schema evolution. */\
  if (u__tmp.type == 0) return u__tmp;\
  u__tmp.value = NS ## generic_vec_at(uv__tmp.value, i__tmp); return u__tmp; }\
static inline NS ## string_t T ## _union_vec_at_as_string(T ## _union_vec_t uv__tmp, size_t i__tmp)\
{ return (NS ## string_t) NS ## generic_vec_at_as_string(uv__tmp.value, i__tmp); }\

#define __flatbuffers_define_union_vector(NS, T)\
typedef NS ## union_vec_t T ## _union_vec_t;\
typedef NS ## mutable_union_vec_t T ## _mutable_union_vec_t;\
static inline T ## _mutable_union_vec_t T ## _mutable_union_vec_cast(T ## _union_vec_t u__tmp)\
{ return NS ## mutable_union_vec_cast(u__tmp); }\
__## NS ## define_union_vector_ops(NS, T)
#define __flatbuffers_define_union(NS, T)\
typedef NS ## union_t T ## _union_t;\
typedef NS ## mutable_union_t T ## _mutable_union_t;\
static inline T ## _mutable_union_t T ## _mutable_union_cast(T ## _union_t u__tmp)\
{ return NS ## mutable_union_cast(u__tmp); }\
__## NS ## define_union_vector(NS, T)
#define __flatbuffers_define_union_vector_field(NS, ID, N, NK, T, r)\
__## NS ## define_vector_field(ID - 1, N, NK ## _type, T ## _vec_t, r)\
__## NS ## define_vector_field(ID, N, NK, flatbuffers_generic_vec_t, r)\
static inline T ## _union_vec_t N ## _ ## NK ## _union(N ## _table_t t__tmp)\
{ T ## _union_vec_t uv__tmp; uv__tmp.type = N ## _ ## NK ## _type_get(t__tmp);\
  uv__tmp.value = N ## _ ## NK(t__tmp);\
  FLATCC_ASSERT(NS ## vec_len(uv__tmp.type) == NS ## vec_len(uv__tmp.value)\
  && "union vector type length mismatch"); return uv__tmp; }
#include <string.h>
static const size_t flatbuffers_not_found = (size_t)-1;
static const size_t flatbuffers_end = (size_t)-1;
#define __flatbuffers_identity(n) (n)
#define __flatbuffers_min(a, b) ((a) < (b) ? (a) : (b))
/* Subtraction doesn't work for unsigned types. */
#define __flatbuffers_scalar_cmp(x, y, n) ((x) < (y) ? -1 : (x) > (y))
static inline int __flatbuffers_string_n_cmp(flatbuffers_string_t v, const char *s, size_t n)
{ size_t nv = flatbuffers_string_len(v); int x = strncmp(v, s, nv < n ? nv : n);
  return x != 0 ? x : nv < n ? -1 : nv > n; }
/* `n` arg unused, but needed by string find macro expansion. */
static inline int __flatbuffers_string_cmp(flatbuffers_string_t v, const char *s, size_t n) { (void)n; return strcmp(v, s); }
/* A = identity if searching scalar vectors rather than key fields. */
/* Returns lowest matching index or not_found. */
#define __flatbuffers_find_by_field(A, V, E, L, K, Kn, T, D)\
{ T v__tmp; size_t a__tmp = 0, b__tmp, m__tmp; if (!(b__tmp = L(V))) { return flatbuffers_not_found; }\
  --b__tmp;\
  while (a__tmp < b__tmp) {\
    m__tmp = a__tmp + ((b__tmp - a__tmp) >> 1);\
    v__tmp = A(E(V, m__tmp));\
    if ((D(v__tmp, (K), (Kn))) < 0) {\
      a__tmp = m__tmp + 1;\
    } else {\
      b__tmp = m__tmp;\
    }\
  }\
  if (a__tmp == b__tmp) {\
    v__tmp = A(E(V, a__tmp));\
    if (D(v__tmp, (K), (Kn)) == 0) {\
       return a__tmp;\
    }\
  }\
  return flatbuffers_not_found;\
}
#define __flatbuffers_find_by_scalar_field(A, V, E, L, K, T)\
__flatbuffers_find_by_field(A, V, E, L, K, 0, T, __flatbuffers_scalar_cmp)
#define __flatbuffers_find_by_string_field(A, V, E, L, K)\
__flatbuffers_find_by_field(A, V, E, L, K, 0, flatbuffers_string_t, __flatbuffers_string_cmp)
#define __flatbuffers_find_by_string_n_field(A, V, E, L, K, Kn)\
__flatbuffers_find_by_field(A, V, E, L, K, Kn, flatbuffers_string_t, __flatbuffers_string_n_cmp)
#define __flatbuffers_define_find_by_scalar_field(N, NK, TK)\
static inline size_t N ## _vec_find_by_ ## NK(N ## _vec_t vec__tmp, TK key__tmp)\
__flatbuffers_find_by_scalar_field(N ## _ ## NK, vec__tmp, N ## _vec_at, N ## _vec_len, key__tmp, TK)
#define __flatbuffers_define_scalar_find(N, T)\
static inline size_t N ## _vec_find(N ## _vec_t vec__tmp, T key__tmp)\
__flatbuffers_find_by_scalar_field(__flatbuffers_identity, vec__tmp, N ## _vec_at, N ## _vec_len, key__tmp, T)
#define __flatbuffers_define_find_by_string_field(N, NK) \
/* Note: find only works on vectors sorted by this field. */\
static inline size_t N ## _vec_find_by_ ## NK(N ## _vec_t vec__tmp, const char *s__tmp)\
__flatbuffers_find_by_string_field(N ## _ ## NK, vec__tmp, N ## _vec_at, N ## _vec_len, s__tmp)\
static inline size_t N ## _vec_find_n_by_ ## NK(N ## _vec_t vec__tmp, const char *s__tmp, size_t n__tmp)\
__flatbuffers_find_by_string_n_field(N ## _ ## NK, vec__tmp, N ## _vec_at, N ## _vec_len, s__tmp, n__tmp)
#define __flatbuffers_define_default_find_by_scalar_field(N, NK, TK)\
static inline size_t N ## _vec_find(N ## _vec_t vec__tmp, TK key__tmp)\
{ return N ## _vec_find_by_ ## NK(vec__tmp, key__tmp); }
#define __flatbuffers_define_default_find_by_string_field(N, NK) \
static inline size_t N ## _vec_find(N ## _vec_t vec__tmp, const char *s__tmp)\
{ return N ## _vec_find_by_ ## NK(vec__tmp, s__tmp); }\
static inline size_t N ## _vec_find_n(N ## _vec_t vec__tmp, const char *s__tmp, size_t n__tmp)\
{ return N ## _vec_find_n_by_ ## NK(vec__tmp, s__tmp, n__tmp); }
/* A = identity if searching scalar vectors rather than key fields. */
/* Returns lowest matching index or not_found. */
#define __flatbuffers_scan_by_field(b, e, A, V, E, L, K, Kn, T, D)\
{ T v__tmp; size_t i__tmp;\
  for (i__tmp = b; i__tmp < e; ++i__tmp) {\
    v__tmp = A(E(V, i__tmp));\
    if (D(v__tmp, (K), (Kn)) == 0) {\
       return i__tmp;\
    }\
  }\
  return flatbuffers_not_found;\
}
#define __flatbuffers_rscan_by_field(b, e, A, V, E, L, K, Kn, T, D)\
{ T v__tmp; size_t i__tmp = e;\
  while (i__tmp-- > b) {\
    v__tmp = A(E(V, i__tmp));\
    if (D(v__tmp, (K), (Kn)) == 0) {\
       return i__tmp;\
    }\
  }\
  return flatbuffers_not_found;\
}
#define __flatbuffers_scan_by_scalar_field(b, e, A, V, E, L, K, T)\
__flatbuffers_scan_by_field(b, e, A, V, E, L, K, 0, T, __flatbuffers_scalar_cmp)
#define __flatbuffers_scan_by_string_field(b, e, A, V, E, L, K)\
__flatbuffers_scan_by_field(b, e, A, V, E, L, K, 0, flatbuffers_string_t, __flatbuffers_string_cmp)
#define __flatbuffers_scan_by_string_n_field(b, e, A, V, E, L, K, Kn)\
__flatbuffers_scan_by_field(b, e, A, V, E, L, K, Kn, flatbuffers_string_t, __flatbuffers_string_n_cmp)
#define __flatbuffers_rscan_by_scalar_field(b, e, A, V, E, L, K, T)\
__flatbuffers_rscan_by_field(b, e, A, V, E, L, K, 0, T, __flatbuffers_scalar_cmp)
#define __flatbuffers_rscan_by_string_field(b, e, A, V, E, L, K)\
__flatbuffers_rscan_by_field(b, e, A, V, E, L, K, 0, flatbuffers_string_t, __flatbuffers_string_cmp)
#define __flatbuffers_rscan_by_string_n_field(b, e, A, V, E, L, K, Kn)\
__flatbuffers_rscan_by_field(b, e, A, V, E, L, K, Kn, flatbuffers_string_t, __flatbuffers_string_n_cmp)
#define __flatbuffers_define_scan_by_scalar_field(N, NK, T)\
static inline size_t N ## _vec_scan_by_ ## NK(N ## _vec_t vec__tmp, T key__tmp)\
__flatbuffers_scan_by_scalar_field(0, N ## _vec_len(vec__tmp), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, key__tmp, T)\
static inline size_t N ## _vec_scan_ex_by_ ## NK(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, T key__tmp)\
__flatbuffers_scan_by_scalar_field(begin__tmp, __flatbuffers_min(end__tmp, N ## _vec_len(vec__tmp)), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, key__tmp, T)\
static inline size_t N ## _vec_rscan_by_ ## NK(N ## _vec_t vec__tmp, T key__tmp)\
__flatbuffers_rscan_by_scalar_field(0, N ## _vec_len(vec__tmp), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, key__tmp, T)\
static inline size_t N ## _vec_rscan_ex_by_ ## NK(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, T key__tmp)\
__flatbuffers_rscan_by_scalar_field(begin__tmp, __flatbuffers_min(end__tmp, N ## _vec_len(vec__tmp)), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, key__tmp, T)
#define __flatbuffers_define_scalar_scan(N, T)\
static inline size_t N ## _vec_scan(N ## _vec_t vec__tmp, T key__tmp)\
__flatbuffers_scan_by_scalar_field(0, N ## _vec_len(vec__tmp), __flatbuffers_identity, vec__tmp, N ## _vec_at, N ## _vec_len, key__tmp, T)\
static inline size_t N ## _vec_scan_ex(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, T key__tmp)\
__flatbuffers_scan_by_scalar_field(begin__tmp, __flatbuffers_min(end__tmp, N ## _vec_len(vec__tmp)), __flatbuffers_identity, vec__tmp, N ## _vec_at, N ## _vec_len, key__tmp, T)\
static inline size_t N ## _vec_rscan(N ## _vec_t vec__tmp, T key__tmp)\
__flatbuffers_rscan_by_scalar_field(0, N ## _vec_len(vec__tmp), __flatbuffers_identity, vec__tmp, N ## _vec_at, N ## _vec_len, key__tmp, T)\
static inline size_t N ## _vec_rscan_ex(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, T key__tmp)\
__flatbuffers_rscan_by_scalar_field(begin__tmp, __flatbuffers_min(end__tmp, N ## _vec_len(vec__tmp)), __flatbuffers_identity, vec__tmp, N ## _vec_at, N ## _vec_len, key__tmp, T)
#define __flatbuffers_define_scan_by_string_field(N, NK) \
static inline size_t N ## _vec_scan_by_ ## NK(N ## _vec_t vec__tmp, const char *s__tmp)\
__flatbuffers_scan_by_string_field(0, N ## _vec_len(vec__tmp), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, s__tmp)\
static inline size_t N ## _vec_scan_n_by_ ## NK(N ## _vec_t vec__tmp, const char *s__tmp, size_t n__tmp)\
__flatbuffers_scan_by_string_n_field(0, N ## _vec_len(vec__tmp), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, s__tmp, n__tmp)\
static inline size_t N ## _vec_scan_ex_by_ ## NK(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, const char *s__tmp)\
__flatbuffers_scan_by_string_field(begin__tmp, __flatbuffers_min(end__tmp, N ## _vec_len(vec__tmp)), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, s__tmp)\
static inline size_t N ## _vec_scan_ex_n_by_ ## NK(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, const char *s__tmp, size_t n__tmp)\
__flatbuffers_scan_by_string_n_field(begin__tmp, __flatbuffers_min( end__tmp, N ## _vec_len(vec__tmp)), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, s__tmp, n__tmp)\
static inline size_t N ## _vec_rscan_by_ ## NK(N ## _vec_t vec__tmp, const char *s__tmp)\
__flatbuffers_rscan_by_string_field(0, N ## _vec_len(vec__tmp), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, s__tmp)\
static inline size_t N ## _vec_rscan_n_by_ ## NK(N ## _vec_t vec__tmp, const char *s__tmp, size_t n__tmp)\
__flatbuffers_rscan_by_string_n_field(0, N ## _vec_len(vec__tmp), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, s__tmp, n__tmp)\
static inline size_t N ## _vec_rscan_ex_by_ ## NK(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, const char *s__tmp)\
__flatbuffers_rscan_by_string_field(begin__tmp, __flatbuffers_min(end__tmp, N ## _vec_len(vec__tmp)), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, s__tmp)\
static inline size_t N ## _vec_rscan_ex_n_by_ ## NK(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, const char *s__tmp, size_t n__tmp)\
__flatbuffers_rscan_by_string_n_field(begin__tmp, __flatbuffers_min( end__tmp, N ## _vec_len(vec__tmp)), N ## _ ## NK ## _get, vec__tmp, N ## _vec_at, N ## _vec_len, s__tmp, n__tmp)
#define __flatbuffers_define_default_scan_by_scalar_field(N, NK, TK)\
static inline size_t N ## _vec_scan(N ## _vec_t vec__tmp, TK key__tmp)\
{ return N ## _vec_scan_by_ ## NK(vec__tmp, key__tmp); }\
static inline size_t N ## _vec_scan_ex(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, TK key__tmp)\
{ return N ## _vec_scan_ex_by_ ## NK(vec__tmp, begin__tmp, end__tmp, key__tmp); }\
static inline size_t N ## _vec_rscan(N ## _vec_t vec__tmp, TK key__tmp)\
{ return N ## _vec_rscan_by_ ## NK(vec__tmp, key__tmp); }\
static inline size_t N ## _vec_rscan_ex(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, TK key__tmp)\
{ return N ## _vec_rscan_ex_by_ ## NK(vec__tmp, begin__tmp, end__tmp, key__tmp); }
#define __flatbuffers_define_default_scan_by_string_field(N, NK) \
static inline size_t N ## _vec_scan(N ## _vec_t vec__tmp, const char *s__tmp)\
{ return N ## _vec_scan_by_ ## NK(vec__tmp, s__tmp); }\
static inline size_t N ## _vec_scan_n(N ## _vec_t vec__tmp, const char *s__tmp, size_t n__tmp)\
{ return N ## _vec_scan_n_by_ ## NK(vec__tmp, s__tmp, n__tmp); }\
static inline size_t N ## _vec_scan_ex(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, const char *s__tmp)\
{ return N ## _vec_scan_ex_by_ ## NK(vec__tmp, begin__tmp, end__tmp, s__tmp); }\
static inline size_t N ## _vec_scan_ex_n(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, const char *s__tmp, size_t n__tmp)\
{ return N ## _vec_scan_ex_n_by_ ## NK(vec__tmp, begin__tmp, end__tmp, s__tmp, n__tmp); }\
static inline size_t N ## _vec_rscan(N ## _vec_t vec__tmp, const char *s__tmp)\
{ return N ## _vec_rscan_by_ ## NK(vec__tmp, s__tmp); }\
static inline size_t N ## _vec_rscan_n(N ## _vec_t vec__tmp, const char *s__tmp, size_t n__tmp)\
{ return N ## _vec_rscan_n_by_ ## NK(vec__tmp, s__tmp, n__tmp); }\
static inline size_t N ## _vec_rscan_ex(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, const char *s__tmp)\
{ return N ## _vec_rscan_ex_by_ ## NK(vec__tmp, begin__tmp, end__tmp, s__tmp); }\
static inline size_t N ## _vec_rscan_ex_n(N ## _vec_t vec__tmp, size_t begin__tmp, size_t end__tmp, const char *s__tmp, size_t n__tmp)\
{ return N ## _vec_rscan_ex_n_by_ ## NK(vec__tmp, begin__tmp, end__tmp, s__tmp, n__tmp); }
#define __flatbuffers_heap_sort(N, X, A, E, L, TK, TE, D, S)\
static inline void __ ## N ## X ## __heap_sift_down(\
        N ## _mutable_vec_t vec__tmp, size_t start__tmp, size_t end__tmp)\
{ size_t child__tmp, root__tmp; TK v1__tmp, v2__tmp, vroot__tmp;\
  root__tmp = start__tmp;\
  while ((root__tmp << 1) <= end__tmp) {\
    child__tmp = root__tmp << 1;\
    if (child__tmp < end__tmp) {\
      v1__tmp = A(E(vec__tmp, child__tmp));\
      v2__tmp = A(E(vec__tmp, child__tmp + 1));\
      if (D(v1__tmp, v2__tmp) < 0) {\
        child__tmp++;\
      }\
    }\
    vroot__tmp = A(E(vec__tmp, root__tmp));\
    v1__tmp = A(E(vec__tmp, child__tmp));\
    if (D(vroot__tmp, v1__tmp) < 0) {\
      S(vec__tmp, root__tmp, child__tmp, TE);\
      root__tmp = child__tmp;\
    } else {\
      return;\
    }\
  }\
}\
static inline void __ ## N ## X ## __heap_sort(N ## _mutable_vec_t vec__tmp)\
{ size_t start__tmp, end__tmp, size__tmp;\
  size__tmp = L(vec__tmp); if (size__tmp == 0) return; end__tmp = size__tmp - 1; start__tmp = size__tmp >> 1;\
  do { __ ## N ## X ## __heap_sift_down(vec__tmp, start__tmp, end__tmp); } while (start__tmp--);\
  while (end__tmp > 0) { \
    S(vec__tmp, 0, end__tmp, TE);\
    __ ## N ## X ## __heap_sift_down(vec__tmp, 0, --end__tmp); } }
#define __flatbuffers_define_sort_by_field(N, NK, TK, TE, D, S)\
  __flatbuffers_heap_sort(N, _sort_by_ ## NK, N ## _ ## NK ## _get, N ## _vec_at, N ## _vec_len, TK, TE, D, S)\
static inline void N ## _vec_sort_by_ ## NK(N ## _mutable_vec_t vec__tmp)\
{ __ ## N ## _sort_by_ ## NK ## __heap_sort(vec__tmp); }
#define __flatbuffers_define_sort(N, TK, TE, D, S)\
__flatbuffers_heap_sort(N, , __flatbuffers_identity, N ## _vec_at, N ## _vec_len, TK, TE, D, S)\
static inline void N ## _vec_sort(N ## _mutable_vec_t vec__tmp) { __ ## N ## __heap_sort(vec__tmp); }
#define __flatbuffers_scalar_diff(x, y) ((x) < (y) ? -1 : (x) > (y))
#define __flatbuffers_string_diff(x, y) __flatbuffers_string_n_cmp((x), (const char *)(y), flatbuffers_string_len(y))
#define __flatbuffers_value_swap(vec, a, b, TE) { TE x__tmp = vec[b]; vec[b] = vec[a]; vec[a] = x__tmp; }
#define __flatbuffers_uoffset_swap(vec, a, b, TE)\
{ TE ta__tmp, tb__tmp, d__tmp;\
  d__tmp = (TE)((a - b) * sizeof(vec[0]));\
  ta__tmp =  __flatbuffers_uoffset_read_from_pe(vec + b) - d__tmp;\
  tb__tmp =  __flatbuffers_uoffset_read_from_pe(vec + a) + d__tmp;\
  __flatbuffers_uoffset_write_to_pe(vec + a, ta__tmp);\
  __flatbuffers_uoffset_write_to_pe(vec + b, tb__tmp); }
#define __flatbuffers_scalar_swap(vec, a, b, TE) __flatbuffers_value_swap(vec, a, b, TE)
#define __flatbuffers_string_swap(vec, a, b, TE) __flatbuffers_uoffset_swap(vec, a, b, TE)
#define __flatbuffers_struct_swap(vec, a, b, TE) __flatbuffers_value_swap(vec, a, b, TE)
#define __flatbuffers_table_swap(vec, a, b, TE) __flatbuffers_uoffset_swap(vec, a, b, TE)
#define __flatbuffers_define_struct_sort_by_scalar_field(N, NK, TK, TE)\
  __flatbuffers_define_sort_by_field(N, NK, TK, TE, __flatbuffers_scalar_diff, __flatbuffers_struct_swap)
#define __flatbuffers_define_table_sort_by_scalar_field(N, NK, TK)\
  __flatbuffers_define_sort_by_field(N, NK, TK, flatbuffers_uoffset_t, __flatbuffers_scalar_diff, __flatbuffers_table_swap)
#define __flatbuffers_define_table_sort_by_string_field(N, NK)\
  __flatbuffers_define_sort_by_field(N, NK, flatbuffers_string_t, flatbuffers_uoffset_t, __flatbuffers_string_diff, __flatbuffers_table_swap)
#define __flatbuffers_define_scalar_sort(N, T) __flatbuffers_define_sort(N, T, T, __flatbuffers_scalar_diff, __flatbuffers_scalar_swap)
#define __flatbuffers_define_string_sort() __flatbuffers_define_sort(flatbuffers_string, flatbuffers_string_t, flatbuffers_uoffset_t, __flatbuffers_string_diff, __flatbuffers_string_swap)
#define __flatbuffers_sort_vector_field(N, NK, T, t)\
{ T ## _mutable_vec_t v__tmp = (T ## _mutable_vec_t) N ## _ ## NK ## _get(t);\
  if (v__tmp) T ## _vec_sort(v__tmp); }
#define __flatbuffers_sort_table_field(N, NK, T, t)\
{ T ## _sort((T ## _mutable_table_t)N ## _ ## NK ## _get(t)); }
#define __flatbuffers_sort_union_field(N, NK, T, t)\
{ T ## _sort(T ## _mutable_union_cast(N ## _ ## NK ## _union(t))); }
#define __flatbuffers_sort_table_vector_field_elements(N, NK, T, t)\
{ T ## _vec_t v__tmp = N ## _ ## NK ## _get(t); size_t i__tmp, n__tmp;\
  n__tmp = T ## _vec_len(v__tmp); for (i__tmp = 0; i__tmp < n__tmp; ++i__tmp) {\
  T ## _sort((T ## _mutable_table_t)T ## _vec_at(v__tmp, i__tmp)); }}
#define __flatbuffers_sort_union_vector_field_elements(N, NK, T, t)\
{ T ## _union_vec_t v__tmp = N ## _ ## NK ## _union(t); size_t i__tmp, n__tmp;\
  n__tmp = T ## _union_vec_len(v__tmp); for (i__tmp = 0; i__tmp < n__tmp; ++i__tmp) {\
  T ## _sort(T ## _mutable_union_cast(T ## _union_vec_at(v__tmp, i__tmp))); }}
#define __flatbuffers_define_scalar_vector(N, T)\
typedef const T *N ## _vec_t;\
typedef T *N ## _mutable_vec_t;\
__flatbuffers_define_scalar_vec_len(N)\
__flatbuffers_define_scalar_vec_at(N, T)\
__flatbuffers_define_scalar_find(N, T)\
__flatbuffers_define_scalar_scan(N, T)\
__flatbuffers_define_scalar_sort(N, T)

#define __flatbuffers_define_integer_type(N, T, W)\
__flatcc_define_integer_accessors(N, T, W, flatbuffers_endian)\
__flatbuffers_define_scalar_vector(N, T)
__flatbuffers_define_scalar_vector(flatbuffers_bool, flatbuffers_bool_t)
__flatbuffers_define_scalar_vector(flatbuffers_char, char)
__flatbuffers_define_scalar_vector(flatbuffers_uint8, uint8_t)
__flatbuffers_define_scalar_vector(flatbuffers_int8, int8_t)
__flatbuffers_define_scalar_vector(flatbuffers_uint16, uint16_t)
__flatbuffers_define_scalar_vector(flatbuffers_int16, int16_t)
__flatbuffers_define_scalar_vector(flatbuffers_uint32, uint32_t)
__flatbuffers_define_scalar_vector(flatbuffers_int32, int32_t)
__flatbuffers_define_scalar_vector(flatbuffers_uint64, uint64_t)
__flatbuffers_define_scalar_vector(flatbuffers_int64, int64_t)
__flatbuffers_define_scalar_vector(flatbuffers_float, float)
__flatbuffers_define_scalar_vector(flatbuffers_double, double)
__flatbuffers_define_scalar_vector(flatbuffers_union_type, flatbuffers_union_type_t)
static inline size_t flatbuffers_string_vec_find(flatbuffers_string_vec_t vec, const char *s)
__flatbuffers_find_by_string_field(__flatbuffers_identity, vec, flatbuffers_string_vec_at, flatbuffers_string_vec_len, s)
static inline size_t flatbuffers_string_vec_find_n(flatbuffers_string_vec_t vec, const char *s, size_t n)
__flatbuffers_find_by_string_n_field(__flatbuffers_identity, vec, flatbuffers_string_vec_at, flatbuffers_string_vec_len, s, n)
static inline size_t flatbuffers_string_vec_scan(flatbuffers_string_vec_t vec, const char *s)
__flatbuffers_scan_by_string_field(0, flatbuffers_string_vec_len(vec), __flatbuffers_identity, vec, flatbuffers_string_vec_at, flatbuffers_string_vec_len, s)
static inline size_t flatbuffers_string_vec_scan_n(flatbuffers_string_vec_t vec, const char *s, size_t n)
__flatbuffers_scan_by_string_n_field(0, flatbuffers_string_vec_len(vec), __flatbuffers_identity, vec, flatbuffers_string_vec_at, flatbuffers_string_vec_len, s, n)
static inline size_t flatbuffers_string_vec_scan_ex(flatbuffers_string_vec_t vec, size_t begin, size_t end, const char *s)
__flatbuffers_scan_by_string_field(begin, __flatbuffers_min(end, flatbuffers_string_vec_len(vec)), __flatbuffers_identity, vec, flatbuffers_string_vec_at, flatbuffers_string_vec_len, s)
static inline size_t flatbuffers_string_vec_scan_ex_n(flatbuffers_string_vec_t vec, size_t begin, size_t end, const char *s, size_t n)
__flatbuffers_scan_by_string_n_field(begin, __flatbuffers_min(end, flatbuffers_string_vec_len(vec)), __flatbuffers_identity, vec, flatbuffers_string_vec_at, flatbuffers_string_vec_len, s, n)
static inline size_t flatbuffers_string_vec_rscan(flatbuffers_string_vec_t vec, const char *s)
__flatbuffers_rscan_by_string_field(0, flatbuffers_string_vec_len(vec), __flatbuffers_identity, vec, flatbuffers_string_vec_at, flatbuffers_string_vec_len, s)
static inline size_t flatbuffers_string_vec_rscan_n(flatbuffers_string_vec_t vec, const char *s, size_t n)
__flatbuffers_rscan_by_string_n_field(0, flatbuffers_string_vec_len(vec), __flatbuffers_identity, vec, flatbuffers_string_vec_at, flatbuffers_string_vec_len, s, n)
static inline size_t flatbuffers_string_vec_rscan_ex(flatbuffers_string_vec_t vec, size_t begin, size_t end, const char *s)
__flatbuffers_rscan_by_string_field(begin, __flatbuffers_min(end, flatbuffers_string_vec_len(vec)), __flatbuffers_identity, vec, flatbuffers_string_vec_at, flatbuffers_string_vec_len, s)
static inline size_t flatbuffers_string_vec_rscan_ex_n(flatbuffers_string_vec_t vec, size_t begin, size_t end, const char *s, size_t n)
__flatbuffers_rscan_by_string_n_field(begin, __flatbuffers_min(end, flatbuffers_string_vec_len(vec)), __flatbuffers_identity, vec, flatbuffers_string_vec_at, flatbuffers_string_vec_len, s, n)
__flatbuffers_define_string_sort()
#define __flatbuffers_define_struct_scalar_fixed_array_field(N, NK, TK, T, L)\
static inline T N ## _ ## NK ## _get(N ## _struct_t t__tmp, size_t i__tmp)\
{ if (!t__tmp || i__tmp >= L) return 0;\
  return __flatbuffers_read_scalar(TK, &(t__tmp->NK[i__tmp])); }\
static inline const T *N ## _ ## NK ## _get_ptr(N ## _struct_t t__tmp)\
{ return t__tmp ? t__tmp->NK : 0; }\
static inline size_t N ## _ ## NK ## _get_len(void) { return L; }
#define __flatbuffers_define_struct_struct_fixed_array_field(N, NK, T, L)\
static inline T N ## _ ## NK ## _get(N ## _struct_t t__tmp, size_t i__tmp)\
{ if (!t__tmp || i__tmp >= L) return 0; return t__tmp->NK + i__tmp; }static inline T N ## _ ## NK ## _get_ptr(N ## _struct_t t__tmp)\
{ return t__tmp ? t__tmp->NK : 0; }\
static inline size_t N ## _ ## NK ## _get_len(void) { return L; }
#define __flatbuffers_define_struct_scalar_field(N, NK, TK, T)\
static inline T N ## _ ## NK ## _get(N ## _struct_t t__tmp)\
{ return t__tmp ? __flatbuffers_read_scalar(TK, &(t__tmp->NK)) : 0; }\
static inline const T *N ## _ ## NK ## _get_ptr(N ## _struct_t t__tmp)\
{ return t__tmp ? &(t__tmp->NK) : 0; }\
__flatbuffers_define_scan_by_scalar_field(N, NK, T)
#define __flatbuffers_define_struct_struct_field(N, NK, T)\
static inline T N ## _ ## NK ## _get(N ## _struct_t t__tmp) { return t__tmp ? &(t__tmp->NK) : 0; }
/* If fid is null, the function returns true without testing as buffer is not expected to have any id. */
static inline int flatbuffers_has_identifier(const void *buffer, const char *fid)
{ flatbuffers_thash_t id, id2 = 0; if (fid == 0) { return 1; };
  id2 = flatbuffers_type_hash_from_string(fid);
  id = __flatbuffers_thash_read_from_pe(((flatbuffers_uoffset_t *)buffer) + 1);
  return id2 == 0 || id == id2; }
static inline int flatbuffers_has_type_hash(const void *buffer, flatbuffers_thash_t thash)
{ return thash == 0 || (__flatbuffers_thash_read_from_pe((flatbuffers_uoffset_t *)buffer + 1) == thash); }

static inline flatbuffers_thash_t flatbuffers_get_type_hash(const void *buffer)
{ return __flatbuffers_thash_read_from_pe((flatbuffers_uoffset_t *)buffer + 1); }

#define flatbuffers_verify_endian() flatbuffers_has_identifier("\x00\x00\x00\x00" "1234", "1234")
static inline void *flatbuffers_read_size_prefix(void *b, size_t *size_out)
{ if (size_out) { *size_out = (size_t)__flatbuffers_uoffset_read_from_pe(b); }
  return (uint8_t *)b + sizeof(flatbuffers_uoffset_t); }
/* Null file identifier accepts anything, otherwise fid should be 4 characters. */
#define __flatbuffers_read_root(T, K, buffer, fid)\
  ((!buffer || !flatbuffers_has_identifier(buffer, fid)) ? 0 :\
  ((T ## _ ## K ## t)(((uint8_t *)buffer) +\
    __flatbuffers_uoffset_read_from_pe(buffer))))
#define __flatbuffers_read_typed_root(T, K, buffer, thash)\
  ((!buffer || !flatbuffers_has_type_hash(buffer, thash)) ? 0 :\
  ((T ## _ ## K ## t)(((uint8_t *)buffer) +\
    __flatbuffers_uoffset_read_from_pe(buffer))))
#define __flatbuffers_nested_buffer_as_root(C, N, T, K)\
static inline T ## _ ## K ## t C ## _ ## N ## _as_root_with_identifier(C ## _ ## table_t t__tmp, const char *fid__tmp)\
{ const uint8_t *buffer__tmp = C ## _ ## N(t__tmp); return __flatbuffers_read_root(T, K, buffer__tmp, fid__tmp); }\
static inline T ## _ ## K ## t C ## _ ## N ## _as_typed_root(C ## _ ## table_t t__tmp)\
{ const uint8_t *buffer__tmp = C ## _ ## N(t__tmp); return __flatbuffers_read_root(T, K, buffer__tmp, C ## _ ## type_identifier); }\
static inline T ## _ ## K ## t C ## _ ## N ## _as_root(C ## _ ## table_t t__tmp)\
{ const char *fid__tmp = T ## _file_identifier;\
  const uint8_t *buffer__tmp = C ## _ ## N(t__tmp); return __flatbuffers_read_root(T, K, buffer__tmp, fid__tmp); }
#define __flatbuffers_buffer_as_root(N, K)\
static inline N ## _ ## K ## t N ## _as_root_with_identifier(const void *buffer__tmp, const char *fid__tmp)\
{ return __flatbuffers_read_root(N, K, buffer__tmp, fid__tmp); }\
static inline N ## _ ## K ## t N ## _as_root_with_type_hash(const void *buffer__tmp, flatbuffers_thash_t thash__tmp)\
{ return __flatbuffers_read_typed_root(N, K, buffer__tmp, thash__tmp); }\
static inline N ## _ ## K ## t N ## _as_root(const void *buffer__tmp)\
{ const char *fid__tmp = N ## _file_identifier;\
  return __flatbuffers_read_root(N, K, buffer__tmp, fid__tmp); }\
static inline N ## _ ## K ## t N ## _as_typed_root(const void *buffer__tmp)\
{ return __flatbuffers_read_typed_root(N, K, buffer__tmp, N ## _type_hash); }
#define __flatbuffers_struct_as_root(N) __flatbuffers_buffer_as_root(N, struct_)
#define __flatbuffers_table_as_root(N) __flatbuffers_buffer_as_root(N, table_)

#include "flatcc/flatcc_epilogue.h"
#endif /* FLATBUFFERS_COMMON_H */
