/*!
 ******************************************************************************
 *
 * \file
 *
 * \brief   Header file containing RAJA index set iteration template 
 *          methods for OpenMP execution policies.
 *
 *          These methods should work on any platform.
 *
 * \author  Rich Hornung, Center for Applied Scientific Computing, LLNL
 * \author  Jeff Keasler, Applications, Simulations And Quality, LLNL
 *
 ******************************************************************************
 */

#ifndef RAJA_forall_omp_any_HXX
#define RAJA_forall_omp_any_HXX

#include "config.hxx"

#include "int_datatypes.hxx"

#include "RAJAVec.hxx"

#include "execpolicy.hxx"

#include "fault_tolerance.hxx"

#include <omp.h>


namespace RAJA {


//
//////////////////////////////////////////////////////////////////////
//
// Function templates that iterate over range index sets.
//
//////////////////////////////////////////////////////////////////////
//

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over index range.
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall(omp_parallel_for_exec,
            const Index_type begin, const Index_type end, 
            LOOP_BODY loop_body)
{
   RAJA_FT_BEGIN ;

#pragma omp parallel for
   for ( Index_type ii = begin ; ii < end ; ++ii ) {
      loop_body( ii );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over index range, including index count.
 *
 *         NOTE: lambda loop body requires two args (icount, index).
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall_Icount(omp_parallel_for_exec,
                   const Index_type begin, const Index_type end,
                   const Index_type icount,
                   LOOP_BODY loop_body)
{
   const Index_type loop_end = end - begin + 1;

   RAJA_FT_BEGIN ;

#pragma omp parallel for
   for ( Index_type ii = 0 ; ii < loop_end ; ++ii ) {
      loop_body( ii+icount, ii+begin );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over index range set object.
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall(omp_parallel_for_exec,
            const RangeSegment& iseg,
            LOOP_BODY loop_body)
{
   const Index_type begin = iseg.getBegin();
   const Index_type end   = iseg.getEnd();

   RAJA_FT_BEGIN ;

#pragma omp parallel for
   for ( Index_type ii = begin ; ii < end ; ++ii ) {
      loop_body( ii );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over index range set object,
 *         including index count.
 *
 *         NOTE: lambda loop body requires two args (icount, index).
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall_Icount(omp_parallel_for_exec,
                   const RangeSegment& iseg,
                   const Index_type icount,
                   LOOP_BODY loop_body)
{           
   const Index_type begin = iseg.getBegin();
   const Index_type loop_end = iseg.getEnd() - begin + 1;

   RAJA_FT_BEGIN ;

#pragma omp parallel for
   for ( Index_type ii = 0 ; ii < loop_end ; ++ii ) {
      loop_body( ii+icount, ii+begin );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for minloc reduction over index range.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_minloc(omp_parallel_for_exec,
                   const Index_type begin, const Index_type end,
                   T* min, Index_type *loc,
                   LOOP_BODY loop_body)
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> min_tmp(nthreads);
   RAJAVec<Index_type> loc_tmp(nthreads);

   RAJA_FT_BEGIN ;

   for ( int i = 0; i < nthreads; ++i ) {
       min_tmp[i] = *min ;
       loc_tmp[i] = *loc ;
   }

#pragma omp parallel for
   for ( Index_type ii = begin ; ii < end ; ++ii ) {
      loop_body( ii, &min_tmp[omp_get_thread_num()],
                     &loc_tmp[omp_get_thread_num()] );
   }

   for ( int i = 1; i < nthreads; ++i ) {
      if ( min_tmp[i] < min_tmp[0] ) {
         min_tmp[0] = min_tmp[i];
         loc_tmp[0] = loc_tmp[i];
      }
   }

   RAJA_FT_END ;

   *min = min_tmp[0] ;
   *loc = loc_tmp[0] ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for minloc reduction over range index set object.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_minloc(omp_parallel_for_exec,
                   const RangeSegment& iseg,
                   T* min, Index_type *loc,
                   LOOP_BODY loop_body)
{
   forall_minloc(omp_parallel_for_exec(),
                 iseg.getBegin(), iseg.getEnd(),
                 min, loc,
                 loop_body);
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for maxloc reduction over index range.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_maxloc(omp_parallel_for_exec,
                   const Index_type begin, const Index_type end,
                   T* max, Index_type *loc,
                   LOOP_BODY loop_body)
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> max_tmp(nthreads);
   RAJAVec<Index_type> loc_tmp(nthreads);

   RAJA_FT_BEGIN ;

   for ( int i = 0; i < nthreads; ++i ) {
       max_tmp[i] = *max ;
       loc_tmp[i] = *loc ;
   }

#pragma omp parallel for 
   for ( Index_type ii = begin ; ii < end ; ++ii ) {
      loop_body( ii, &max_tmp[omp_get_thread_num()],
                     &loc_tmp[omp_get_thread_num()] );
   }

   for ( int i = 1; i < nthreads; ++i ) {
      if ( max_tmp[i] > max_tmp[0] ) {
         max_tmp[0] = max_tmp[i];
         loc_tmp[0] = loc_tmp[i];
      }
   }

   RAJA_FT_END ;

   *max = max_tmp[0] ;
   *loc = loc_tmp[0] ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for maxloc reduction over range index set object.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_maxloc(omp_parallel_for_exec,
                   const RangeSegment& iseg,
                   T* max, Index_type *loc,
                   LOOP_BODY loop_body)
{
   forall_maxloc(omp_parallel_for_exec(),
                 iseg.getBegin(), iseg.getEnd(),
                 max, loc,
                 loop_body);
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for sum reduction over index range.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_sum(omp_parallel_for_exec,
                const Index_type begin, const Index_type end,
                T* sum,
                LOOP_BODY loop_body)
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> sum_tmp(nthreads);

   RAJA_FT_BEGIN ;

   for ( int i = 0; i < nthreads; ++i ) {
      sum_tmp[i] = 0 ;
   }

#pragma omp parallel for
   for ( Index_type ii = begin ; ii < end ; ++ii ) {
      loop_body( ii, &sum_tmp[omp_get_thread_num()] );
   }

   RAJA_FT_END ;

   for ( int i = 0; i < nthreads; ++i ) {
      *sum += sum_tmp[i];
   }
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for sum reduction over range index set object.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_sum(omp_parallel_for_exec,
                const RangeSegment& iseg,
                T* sum, 
                LOOP_BODY loop_body)
{
   forall_sum(omp_parallel_for_exec(),
              iseg.getBegin(), iseg.getEnd(),
              sum,
              loop_body);
}

//
//////////////////////////////////////////////////////////////////////
//
// Function templates that iterate over range index sets with stride.
//
//////////////////////////////////////////////////////////////////////
//

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over index range with stride.
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall(omp_parallel_for_exec,
            const Index_type begin, const Index_type end, 
            const Index_type stride,
            LOOP_BODY loop_body)
{
   RAJA_FT_BEGIN ;

#pragma omp parallel for
   for ( Index_type ii = begin ; ii < end ; ii += stride ) {
      loop_body( ii );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over index range with stride,
 *         including index count.
 *
 *         NOTE: lambda loop body requires two args (icount, index).
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall_Icount(omp_parallel_for_exec,
                   const Index_type begin, const Index_type end,
                   const Index_type stride,
                   const Index_type icount,
                   LOOP_BODY loop_body)
{
   const Index_type loop_end = (end-begin)/stride + 1;

   RAJA_FT_BEGIN ;

#pragma omp parallel for
   for ( Index_type ii = 0 ; ii < loop_end ; ++ii ) {
      loop_body( ii+icount, begin + ii*stride );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over range index set with stride object.
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall(omp_parallel_for_exec,
            const RangeStrideSegment& iseg,
            LOOP_BODY loop_body)
{
   const Index_type begin  = iseg.getBegin();
   const Index_type end    = iseg.getEnd();
   const Index_type stride = iseg.getStride();

   RAJA_FT_BEGIN ;

#pragma omp parallel for
   for ( Index_type ii = begin ; ii < end ; ii += stride ) {
      loop_body( ii );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over range index set with stride object,
 *         including index count.
 *
 *         NOTE: lambda loop body requires two args (icount, index).
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall_Icount(omp_parallel_for_exec,
                   const RangeStrideSegment& iseg,
                   const Index_type icount,
                   LOOP_BODY loop_body)
{
   const Index_type begin    = iseg.getBegin();
   const Index_type stride   = iseg.getStride();
   const Index_type loop_end = (iseg.getEnd()-begin)/stride + 1;

   RAJA_FT_BEGIN ;

#pragma omp parallel for
   for ( Index_type ii = 0 ; ii < loop_end ; ++ii ) {
      loop_body( ii+icount, begin + ii*stride );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for minloc reduction over index range with stride.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_minloc(omp_parallel_for_exec,
                   const Index_type begin, const Index_type end,
                   const Index_type stride,
                   T* min, Index_type *loc,
                   LOOP_BODY loop_body)
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> min_tmp(nthreads);
   RAJAVec<Index_type> loc_tmp(nthreads);

   RAJA_FT_BEGIN ;

   for ( int i = 0; i < nthreads; ++i ) {
       min_tmp[i] = *min ;
       loc_tmp[i] = *loc ;
   }

#pragma omp parallel for
   for ( Index_type ii = begin ; ii < end ; ii += stride ) {
      loop_body( ii, &min_tmp[omp_get_thread_num()],
                     &loc_tmp[omp_get_thread_num()] );
   }

   for ( int i = 1; i < nthreads; ++i ) {
      if ( min_tmp[i] < min_tmp[0] ) {
         min_tmp[0] = min_tmp[i];
         loc_tmp[0] = loc_tmp[i];
      }
   }

   RAJA_FT_END ;

   *min = min_tmp[0] ;
   *loc = loc_tmp[0] ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for minloc reduction over 
 *         range index set with stride object.
 *
 ******************************************************************************
 */
template <typename T, 
          typename LOOP_BODY>
RAJA_INLINE
void forall_minloc(omp_parallel_for_exec,
                   const RangeStrideSegment& iseg,
                   T* min, Index_type *loc,
                   LOOP_BODY loop_body)
{
   forall_minloc(omp_parallel_for_exec(),
                 iseg.getBegin(), iseg.getEnd(), iseg.getStride(),
                 min, loc,
                 loop_body);
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for maxloc reduction over index range with stride.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_maxloc(omp_parallel_for_exec,
                   const Index_type begin, const Index_type end, 
                   const Index_type stride,
                   T* max, Index_type *loc,
                   LOOP_BODY loop_body)
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> max_tmp(nthreads);
   RAJAVec<Index_type> loc_tmp(nthreads);

   RAJA_FT_BEGIN ;

   for ( int i = 0; i < nthreads; ++i ) {
       max_tmp[i] = *max ;
       loc_tmp[i] = *loc ;
   }

#pragma omp parallel for
   for ( Index_type ii = begin ; ii < end ; ii += stride ) {
      loop_body( ii, &max_tmp[omp_get_thread_num()],
                     &loc_tmp[omp_get_thread_num()] );
   }

   for ( int i = 1; i < nthreads; ++i ) {
      if ( max_tmp[i] > max_tmp[0] ) {
         max_tmp[0] = max_tmp[i];
         loc_tmp[0] = loc_tmp[i];
      }
   }

   RAJA_FT_END ;

   *max = max_tmp[0] ;
   *loc = loc_tmp[0] ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for maxloc reduction over
 *         range index set with stride object.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_maxloc(omp_parallel_for_exec,
                   const RangeStrideSegment& iseg,
                   T* max, Index_type *loc,
                   LOOP_BODY loop_body)
{
   forall_maxloc(omp_parallel_for_exec(),
                 iseg.getBegin(), iseg.getEnd(), iseg.getStride(),
                 max, loc,
                 loop_body);
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for sum reduction over index range with stride.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_sum(omp_parallel_for_exec,
                const Index_type begin, const Index_type end, 
                const Index_type stride,
                T* sum,
                LOOP_BODY loop_body)
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> sum_tmp(nthreads);

   RAJA_FT_BEGIN ;

   for ( Index_type i = 0; i < nthreads; ++i ) {
      sum_tmp[i] = 0 ;
   }

#pragma omp parallel for
   for ( Index_type ii = begin ; ii < end ; ii += stride ) {
      loop_body( ii, &sum_tmp[omp_get_thread_num()] );
   }

   RAJA_FT_END ;

   for ( int i = 0; i < nthreads; ++i ) {
      *sum += sum_tmp[i];
   }
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for sum reduction over
 *         range index set with stride object.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_sum(omp_parallel_for_exec,
                const RangeStrideSegment& iseg,
                T* sum,
                LOOP_BODY loop_body)
{
   forall_sum(omp_parallel_for_exec(),
              iseg.getBegin(), iseg.getEnd(), iseg.getStride(),
              sum,
              loop_body);
}



//
//////////////////////////////////////////////////////////////////////
//
// Function templates that iterate over list segments.
//
//////////////////////////////////////////////////////////////////////
//

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over indirection array.
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall(omp_parallel_for_exec,
            const Index_type* __restrict__ idx, const Index_type len,
            LOOP_BODY loop_body)
{
   RAJA_FT_BEGIN ;

#pragma novector
#pragma omp parallel for
   for ( Index_type k = 0 ; k < len ; ++k ) {
      loop_body( idx[k] );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over indirection array,
 *         including index count.
 *
 *         NOTE: lambda loop body requires two args (icount, index).
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall_Icount(omp_parallel_for_exec,
                   const Index_type* __restrict__ idx, const Index_type len,
                   const Index_type icount,
                   LOOP_BODY loop_body)
{
   RAJA_FT_BEGIN ;

#pragma novector
#pragma omp parallel for
   for ( Index_type k = 0 ; k < len ; ++k ) {
      loop_body( k+icount, idx[k] );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over list segment object.
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall(omp_parallel_for_exec,
            const ListSegment& iseg,
            LOOP_BODY loop_body)
{
   const Index_type* __restrict__ idx = iseg.getIndex();
   const Index_type len = iseg.getLength();

   RAJA_FT_BEGIN ;

#pragma novector
#pragma omp parallel for
   for ( Index_type k = 0 ; k < len ; ++k ) {
      loop_body( idx[k] );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for iteration over list segment object,
 *         including index count.
 *
 *         NOTE: lambda loop body requires two args (icount, index).
 *
 ******************************************************************************
 */
template <typename LOOP_BODY>
RAJA_INLINE
void forall_Icount(omp_parallel_for_exec,
                   const ListSegment& iseg,
                   const Index_type icount,
                   LOOP_BODY loop_body)
{
   const Index_type* __restrict__ idx = iseg.getIndex();
   const Index_type len = iseg.getLength();

   RAJA_FT_BEGIN ;

#pragma novector
#pragma omp parallel for
   for ( Index_type k = 0 ; k < len ; ++k ) {
      loop_body( k+icount, idx[k] );
   }

   RAJA_FT_END ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for minloc reduction over given indirection array.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_minloc(omp_parallel_for_exec,
                   const Index_type* __restrict__ idx, const Index_type len,
                   T* min, Index_type *loc,
                   LOOP_BODY loop_body)
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> min_tmp(nthreads);
   RAJAVec<Index_type> loc_tmp(nthreads);

   RAJA_FT_BEGIN ;

   for ( int i = 0; i < nthreads; ++i ) {
       min_tmp[i] = *min ;
       loc_tmp[i] = *loc ;
   }

#pragma novector
#pragma omp parallel for
   for ( Index_type k = 0 ; k < len ; ++k ) {
      loop_body( idx[k], &min_tmp[omp_get_thread_num()], 
                         &loc_tmp[omp_get_thread_num()] );
   }

   for ( int i = 1; i < nthreads; ++i ) {
      if ( min_tmp[i] < min_tmp[0] ) {
         min_tmp[0] = min_tmp[i];
         loc_tmp[0] = loc_tmp[i];
      }
   }

   RAJA_FT_END ;

   *min = min_tmp[0] ;
   *loc = loc_tmp[0] ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for minloc reduction over list segment object.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_minloc(omp_parallel_for_exec,
                   const ListSegment& iseg,
                   T* min, Index_type *loc,
                   LOOP_BODY loop_body)
{
   forall_minloc(omp_parallel_for_exec(),
                 iseg.getIndex(), iseg.getLength(),
                 min, loc,
                 loop_body);
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for maxloc reduction over given indirection array.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_maxloc(omp_parallel_for_exec,
                   const Index_type* __restrict__ idx, const Index_type len,
                   T* max, Index_type *loc,
                   LOOP_BODY loop_body)
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> max_tmp(nthreads);
   RAJAVec<Index_type> loc_tmp(nthreads);

   RAJA_FT_BEGIN ;

   for ( int i = 0; i < nthreads; ++i ) {
       max_tmp[i] = *max ;
       loc_tmp[i] = *loc ;
   }

#pragma novector
#pragma omp parallel for
   for ( Index_type k = 0 ; k < len ; ++k ) {
      loop_body( idx[k], &max_tmp[omp_get_thread_num()],
                         &loc_tmp[omp_get_thread_num()] );
   }

   for ( int i = 1; i < nthreads; ++i ) {
      if ( max_tmp[i] > max_tmp[0] ) {
         max_tmp[0] = max_tmp[i];
         loc_tmp[0] = loc_tmp[i];
      }
   }

   RAJA_FT_END ;

   *max = max_tmp[0] ;
   *loc = loc_tmp[0] ;
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for maxloc reduction over list segment object.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_maxloc(omp_parallel_for_exec,
                   const ListSegment& iseg,
                   T* max, Index_type *loc,
                   LOOP_BODY loop_body)
{
   forall_maxloc(omp_parallel_for_exec(),
                 iseg.getIndex(), iseg.getLength(),
                 max, loc,
                 loop_body);
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for sum reduction over given indirection array.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_sum(omp_parallel_for_exec,
                const Index_type* __restrict__ idx, const Index_type len,
                T* sum,
                LOOP_BODY loop_body)
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> sum_tmp(nthreads);

   RAJA_FT_BEGIN ;
   for ( int i = 0; i < nthreads; ++i ) {
      sum_tmp[i] = 0 ;
   }

#pragma novector
#pragma omp parallel for
   for ( Index_type k = 0 ; k < len ; ++k ) {
      loop_body( idx[k], &sum_tmp[omp_get_thread_num()] );
   }

   RAJA_FT_END ;

   for ( int i = 0; i < nthreads; ++i ) {
      *sum += sum_tmp[i];
   }
}

/*!
 ******************************************************************************
 *
 * \brief  omp parallel for sum reduction over list segment object.
 *
 ******************************************************************************
 */
template <typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_sum(omp_parallel_for_exec,
                const ListSegment& iseg,
                T* sum,
                LOOP_BODY loop_body)
{
   forall_sum(omp_parallel_for_exec(),
              iseg.getIndex(), iseg.getLength(),
              sum,
              loop_body);
}


//
//////////////////////////////////////////////////////////////////////
//
// The following function templates iterate over index set
// segments using omp execution policies.
//
//////////////////////////////////////////////////////////////////////
//

/*!
 ******************************************************************************
 *
 * \brief  Iterate over index set segments using omp parallel for 
 *         execution policy and use execution policy template parameter 
 *         for segments.
 *
 ******************************************************************************
 */
template <typename SEG_EXEC_POLICY_T,
          typename LOOP_BODY>
RAJA_INLINE
void forall( IndexSet::ExecPolicy<omp_parallel_for_segit, SEG_EXEC_POLICY_T>,
             const IndexSet& iset, LOOP_BODY loop_body )
{
   const int num_seg = iset.getNumSegments();

#pragma omp parallel for schedule(dynamic, 1)
   for ( int isi = 0; isi < num_seg; ++isi ) {

      const BaseSegment* iseg = iset.getSegment(isi);
      SegmentType segtype = iseg->getType();

      switch ( segtype ) {

         case _RangeSeg_ : {
            forall(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const RangeSegment*>(iseg)),
               loop_body
            );
            break;
         }

#if 0  // RDH RETHINK
         case _RangeStrideSeg_ : {
            forall(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const RangeStrideSegment*>(iseg)),
               loop_body
            );
            break;
         }
#endif

         case _ListSeg_ : {
            forall(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const ListSegment*>(iseg)),
               loop_body
            );
            break;
         }

         default : {
         }

      }  // switch on segment type

   } // iterate over segments of index set
}

/*!
 ******************************************************************************
 *
 * \brief  Iterate over index set segments using omp parallel for
 *         execution policy and use execution policy template parameter
 *         for segments.
 *
 *         This method passes index count to segment iteration.
 *
 *         NOTE: lambda loop body requires two args (icount, index).
 *
 ******************************************************************************
 */
template <typename SEG_EXEC_POLICY_T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_Icount( IndexSet::ExecPolicy<omp_parallel_for_segit, SEG_EXEC_POLICY_T>,
                    const IndexSet& iset, LOOP_BODY loop_body )
{
   const int num_seg = iset.getNumSegments();

#pragma omp parallel for schedule(dynamic, 1)
   for ( int isi = 0; isi < num_seg; ++isi ) {

      const BaseSegment* iseg = iset.getSegment(isi);
      SegmentType segtype = iseg->getType();
      Index_type icount = iseg->getIcount();

      switch ( segtype ) {

         case _RangeSeg_ : {
            forall_Icount(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const RangeSegment*>(iseg)),
               icount,
               loop_body
            );
            break;
         }

#if 0  // RDH RETHINK
         case _RangeStrideSeg_ : {
            forall_Icount(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const RangeStrideSegment*>(iseg)),
               icount,
               loop_body
            );
            break;
         }
#endif

         case _ListSeg_ : {
            forall_Icount(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const ListSegment*>(iseg)),
               icount,
               loop_body
            );
            break;
         }

         default : {
         }

      }  // switch on segment type

   } // iterate over segments of index set
}

/*!
 ******************************************************************************
 *
 * \brief  Minloc operation that iterates over index set segments 
 *         using omp parallel for execution policy and uses execution 
 *         policy template parameter to execute segments.
 *
 ******************************************************************************
 */
template <typename SEG_EXEC_POLICY_T,
          typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_minloc( IndexSet::ExecPolicy<omp_parallel_for_segit, SEG_EXEC_POLICY_T>,
                    const IndexSet& iset, 
                    T* min, Index_type *loc,
                    LOOP_BODY loop_body )
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> min_tmp(nthreads);
   RAJAVec<Index_type> loc_tmp(nthreads);

   for ( int i = 0; i < nthreads; ++i ) {
       min_tmp[i] = *min ;
       loc_tmp[i] = *loc ;
   }

   const int num_seg = iset.getNumSegments();

#pragma omp parallel for 
   for ( int isi = 0; isi < num_seg; ++isi ) {

      const BaseSegment* iseg = iset.getSegment(isi);
      SegmentType segtype = iseg->getType();

      switch ( segtype ) {

         case _RangeSeg_ : {
            forall_minloc(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const RangeSegment*>(iseg)),
               &min_tmp[omp_get_thread_num()], 
               &loc_tmp[omp_get_thread_num()],
               loop_body
            );
            break;
         }

#if 0  // RDH RETHINK
         case _RangeStrideSeg_ : {
            forall_minloc(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const RangeStrideSegment*>(iseg)),
               &min_tmp[omp_get_thread_num()], 
               &loc_tmp[omp_get_thread_num()],
               loop_body
            );
            break;
         }
#endif

         case _ListSeg_ : {
            forall_minloc(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const ListSegment*>(iseg)),
               &min_tmp[omp_get_thread_num()], 
               &loc_tmp[omp_get_thread_num()],
               loop_body
            );
            break;
         }

         default : {
         }

      }  // switch on segment type

   } // iterate over segments of index set

   for ( int i = 1; i < nthreads; ++i ) {
      if ( min_tmp[i] < min_tmp[0] ) {
         min_tmp[0] = min_tmp[i];
         loc_tmp[0] = loc_tmp[i];
      }
   }

   *min = min_tmp[0] ;
   *loc = loc_tmp[0] ;
}

/*!
 ******************************************************************************
 *
 * \brief  Maxloc operation that iterates over index set segments 
 *         using omp parallel for execution policy and uses execution 
 *         policy template parameter to execute segments.
 *
 ******************************************************************************
 */
template <typename SEG_EXEC_POLICY_T,
          typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_maxloc( IndexSet::ExecPolicy<omp_parallel_for_segit, SEG_EXEC_POLICY_T>,
                    const IndexSet& iset, 
                    T* max, Index_type *loc,
                    LOOP_BODY loop_body )
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> max_tmp(nthreads);
   RAJAVec<Index_type> loc_tmp(nthreads);

   for ( int i = 0; i < nthreads; ++i ) {
       max_tmp[i] = *max ;
       loc_tmp[i] = *loc ;
   }

   const int num_seg = iset.getNumSegments();

#pragma omp parallel for
   for ( int isi = 0; isi < num_seg; ++isi ) {

      const BaseSegment* iseg = iset.getSegment(isi);
      SegmentType segtype = iseg->getType();

      switch ( segtype ) {

         case _RangeSeg_ : {
            forall_maxloc(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const RangeSegment*>(iseg)),
               &max_tmp[omp_get_thread_num()], 
               &loc_tmp[omp_get_thread_num()],
               loop_body
            );
            break;
         }

#if 0  // RDH RETHINK
         case _RangeStrideSeg_ : {
            forall_maxloc(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const RangeStrideSegment*>(iseg)),
               &max_tmp[omp_get_thread_num()], 
               &loc_tmp[omp_get_thread_num()],
               loop_body
            );
            break;
         }
#endif

         case _ListSeg_ : {
            forall_maxloc(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const ListSegment*>(iseg)),
               &max_tmp[omp_get_thread_num()], 
               &loc_tmp[omp_get_thread_num()],
               loop_body
            );
            break;
         }

         default : {
         }

      }  // switch on segment type

   } // iterate over segments of index set

   for ( int i = 1; i < nthreads; ++i ) {
      if ( max_tmp[i] > max_tmp[0] ) {
         max_tmp[0] = max_tmp[i];
         loc_tmp[0] = loc_tmp[i];
      }
   }

   *max = max_tmp[0] ;
   *loc = loc_tmp[0] ;
}

/*!
 ******************************************************************************
 *
 * \brief  Sum operation that iterates over index set segments
 *         using omp parallel for execution policy and uses execution
 *         policy template parameter to execute segments.
 *
 ******************************************************************************
 */
template <typename SEG_EXEC_POLICY_T,
          typename T,
          typename LOOP_BODY>
RAJA_INLINE
void forall_sum( IndexSet::ExecPolicy<omp_parallel_for_segit, SEG_EXEC_POLICY_T>,
                 const IndexSet& iset,
                 T* sum,
                 LOOP_BODY loop_body )
{
   const int nthreads = omp_get_max_threads();

   RAJAVec<T> sum_tmp(nthreads);

   for ( int i = 0; i < nthreads; ++i ) {
       sum_tmp[i] = 0 ;
   }

   const int num_seg = iset.getNumSegments();

#pragma omp parallel for
   for ( int isi = 0; isi < num_seg; ++isi ) {

      const BaseSegment* iseg = iset.getSegment(isi);
      SegmentType segtype = iseg->getType();

      switch ( segtype ) {

         case _RangeSeg_ : {
            forall_sum(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const RangeSegment*>(iseg)),
               &sum_tmp[omp_get_thread_num()],
               loop_body
            );
            break;
         }

#if 0  // RDH RETHINK
         case _RangeStrideSeg_ : {
            forall_sum(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const RangeStrideSegment*>(iseg)),
               &sum_tmp[omp_get_thread_num()],
               loop_body
            );
            break;
         }
#endif

         case _ListSeg_ : {
            forall_sum(
               SEG_EXEC_POLICY_T(),
               *(static_cast<const ListSegment*>(iseg)),
               &sum_tmp[omp_get_thread_num()],
               loop_body
            );
            break;
         }

         default : {
         }

      }  // switch on segment type

   } // iterate over segments of index set

   for ( int i = 0; i < nthreads; ++i ) {
      *sum += sum_tmp[i];
   }
}


}  // closing brace for RAJA namespace

#endif  // closing endif for header file include guard
