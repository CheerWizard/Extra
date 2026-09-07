/*
 * Copyright 2026 CheerWizard
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <vulkan/vulkan_enums.hpp>
#if !defined( VULKAN_HPP_NO_TO_STRING )
#  include <vulkan/vulkan_to_string.hpp>
#endif

#ifndef VULKAN_HPP_NO_EXCEPTIONS
VULKAN_HPP_EXPORT namespace std
{
  template <>
  struct is_error_code_enum<VULKAN_HPP_NAMESPACE::Result> : public true_type
  {
  };
}  // namespace std
#endif

VULKAN_HPP_EXPORT namespace VULKAN_HPP_NAMESPACE
{
#ifndef VULKAN_HPP_NO_EXCEPTIONS
  class ErrorCategoryImpl : public std::error_category
  {
  public:
    virtual char const * name() const VULKAN_HPP_NOEXCEPT override
    {
      return VULKAN_HPP_NAMESPACE_STRING "::Result";
    }

    virtual std::string message( int ev ) const override
    {
#  if defined( VULKAN_HPP_NO_TO_STRING )
      return std::to_string( ev );
#  else
      return to_string( static_cast<Result>( ev ) );
#  endif
    }
  };

  class Error
  {
  public:
    Error() VULKAN_HPP_NOEXCEPT                = default;
    Error( Error const & ) VULKAN_HPP_NOEXCEPT = default;
    virtual ~Error() VULKAN_HPP_NOEXCEPT       = default;

    virtual char const * what() const VULKAN_HPP_NOEXCEPT = 0;
  };

  class LogicError
    : public Error
    , public std::logic_error
  {
  public:
    explicit LogicError( std::string const & what ) : Error(), std::logic_error( what ) {}

    explicit LogicError( char const * what ) : Error(), std::logic_error( what ) {}

    virtual char const * what() const VULKAN_HPP_NOEXCEPT
    {
      return std::logic_error::what();
    }
  };

  class SystemError
    : public Error
    , public std::system_error
  {
  public:
    SystemError( std::error_code ec ) : Error(), std::system_error( ec ) {}

    SystemError( std::error_code ec, std::string const & what ) : Error(), std::system_error( ec, what ) {}

    SystemError( std::error_code ec, char const * what ) : Error(), std::system_error( ec, what ) {}

    SystemError( int ev, std::error_category const & ecat ) : Error(), std::system_error( ev, ecat ) {}

    SystemError( int ev, std::error_category const & ecat, std::string const & what ) : Error(), std::system_error( ev, ecat, what ) {}

    SystemError( int ev, std::error_category const & ecat, char const * what ) : Error(), std::system_error( ev, ecat, what ) {}

    virtual char const * what() const VULKAN_HPP_NOEXCEPT
    {
      return std::system_error::what();
    }
  };

  VULKAN_HPP_INLINE std::error_category const & errorCategory() VULKAN_HPP_NOEXCEPT
  {
    static ErrorCategoryImpl instance;
    return instance;
  }

  VULKAN_HPP_INLINE std::error_code make_error_code( Result e ) VULKAN_HPP_NOEXCEPT
  {
    return std::error_code( static_cast<int>( e ), errorCategory() );
  }

  VULKAN_HPP_INLINE std::error_condition make_error_condition( Result e ) VULKAN_HPP_NOEXCEPT
  {
    return std::error_condition( static_cast<int>( e ), errorCategory() );
  }

  class OutOfHostMemoryError : public SystemError
  {
  public:
    OutOfHostMemoryError( std::string const & message ) : SystemError( make_error_code( Result::eErrorOutOfHostMemory ), message ) {}

    OutOfHostMemoryError( char const * message ) : SystemError( make_error_code( Result::eErrorOutOfHostMemory ), message ) {}
  };

  class OutOfDeviceMemoryError : public SystemError
  {
  public:
    OutOfDeviceMemoryError( std::string const & message ) : SystemError( make_error_code( Result::eErrorOutOfDeviceMemory ), message ) {}

    OutOfDeviceMemoryError( char const * message ) : SystemError( make_error_code( Result::eErrorOutOfDeviceMemory ), message ) {}
  };

  class InitializationFailedError : public SystemError
  {
  public:
    InitializationFailedError( std::string const & message ) : SystemError( make_error_code( Result::eErrorInitializationFailed ), message ) {}

    InitializationFailedError( char const * message ) : SystemError( make_error_code( Result::eErrorInitializationFailed ), message ) {}
  };

  class DeviceLostError : public SystemError
  {
  public:
    DeviceLostError( std::string const & message ) : SystemError( make_error_code( Result::eErrorDeviceLost ), message ) {}

    DeviceLostError( char const * message ) : SystemError( make_error_code( Result::eErrorDeviceLost ), message ) {}
  };

  class MemoryMapFailedError : public SystemError
  {
  public:
    MemoryMapFailedError( std::string const & message ) : SystemError( make_error_code( Result::eErrorMemoryMapFailed ), message ) {}

    MemoryMapFailedError( char const * message ) : SystemError( make_error_code( Result::eErrorMemoryMapFailed ), message ) {}
  };

  class LayerNotPresentError : public SystemError
  {
  public:
    LayerNotPresentError( std::string const & message ) : SystemError( make_error_code( Result::eErrorLayerNotPresent ), message ) {}

    LayerNotPresentError( char const * message ) : SystemError( make_error_code( Result::eErrorLayerNotPresent ), message ) {}
  };

  class ExtensionNotPresentError : public SystemError
  {
  public:
    ExtensionNotPresentError( std::string const & message ) : SystemError( make_error_code( Result::eErrorExtensionNotPresent ), message ) {}

    ExtensionNotPresentError( char const * message ) : SystemError( make_error_code( Result::eErrorExtensionNotPresent ), message ) {}
  };

  class FeatureNotPresentError : public SystemError
  {
  public:
    FeatureNotPresentError( std::string const & message ) : SystemError( make_error_code( Result::eErrorFeatureNotPresent ), message ) {}

    FeatureNotPresentError( char const * message ) : SystemError( make_error_code( Result::eErrorFeatureNotPresent ), message ) {}
  };

  class IncompatibleDriverError : public SystemError
  {
  public:
    IncompatibleDriverError( std::string const & message ) : SystemError( make_error_code( Result::eErrorIncompatibleDriver ), message ) {}

    IncompatibleDriverError( char const * message ) : SystemError( make_error_code( Result::eErrorIncompatibleDriver ), message ) {}
  };

  class TooManyObjectsError : public SystemError
  {
  public:
    TooManyObjectsError( std::string const & message ) : SystemError( make_error_code( Result::eErrorTooManyObjects ), message ) {}

    TooManyObjectsError( char const * message ) : SystemError( make_error_code( Result::eErrorTooManyObjects ), message ) {}
  };

  class FormatNotSupportedError : public SystemError
  {
  public:
    FormatNotSupportedError( std::string const & message ) : SystemError( make_error_code( Result::eErrorFormatNotSupported ), message ) {}

    FormatNotSupportedError( char const * message ) : SystemError( make_error_code( Result::eErrorFormatNotSupported ), message ) {}
  };

  class FragmentedPoolError : public SystemError
  {
  public:
    FragmentedPoolError( std::string const & message ) : SystemError( make_error_code( Result::eErrorFragmentedPool ), message ) {}

    FragmentedPoolError( char const * message ) : SystemError( make_error_code( Result::eErrorFragmentedPool ), message ) {}
  };

  class UnknownError : public SystemError
  {
  public:
    UnknownError( std::string const & message ) : SystemError( make_error_code( Result::eErrorUnknown ), message ) {}

    UnknownError( char const * message ) : SystemError( make_error_code( Result::eErrorUnknown ), message ) {}
  };

  class ValidationFailedError : public SystemError
  {
  public:
    ValidationFailedError( std::string const & message ) : SystemError( make_error_code( Result::eErrorValidationFailed ), message ) {}

    ValidationFailedError( char const * message ) : SystemError( make_error_code( Result::eErrorValidationFailed ), message ) {}
  };

  class OutOfPoolMemoryError : public SystemError
  {
  public:
    OutOfPoolMemoryError( std::string const & message ) : SystemError( make_error_code( Result::eErrorOutOfPoolMemory ), message ) {}

    OutOfPoolMemoryError( char const * message ) : SystemError( make_error_code( Result::eErrorOutOfPoolMemory ), message ) {}
  };

  class InvalidExternalHandleError : public SystemError
  {
  public:
    InvalidExternalHandleError( std::string const & message ) : SystemError( make_error_code( Result::eErrorInvalidExternalHandle ), message ) {}

    InvalidExternalHandleError( char const * message ) : SystemError( make_error_code( Result::eErrorInvalidExternalHandle ), message ) {}
  };

  class InvalidOpaqueCaptureAddressError : public SystemError
  {
  public:
    InvalidOpaqueCaptureAddressError( std::string const & message ) : SystemError( make_error_code( Result::eErrorInvalidOpaqueCaptureAddress ), message ) {}

    InvalidOpaqueCaptureAddressError( char const * message ) : SystemError( make_error_code( Result::eErrorInvalidOpaqueCaptureAddress ), message ) {}
  };

  class FragmentationError : public SystemError
  {
  public:
    FragmentationError( std::string const & message ) : SystemError( make_error_code( Result::eErrorFragmentation ), message ) {}

    FragmentationError( char const * message ) : SystemError( make_error_code( Result::eErrorFragmentation ), message ) {}
  };

  class NotPermittedError : public SystemError
  {
  public:
    NotPermittedError( std::string const & message ) : SystemError( make_error_code( Result::eErrorNotPermitted ), message ) {}

    NotPermittedError( char const * message ) : SystemError( make_error_code( Result::eErrorNotPermitted ), message ) {}
  };

  class SurfaceLostKHRError : public SystemError
  {
  public:
    SurfaceLostKHRError( std::string const & message ) : SystemError( make_error_code( Result::eErrorSurfaceLostKHR ), message ) {}

    SurfaceLostKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorSurfaceLostKHR ), message ) {}
  };

  class NativeWindowInUseKHRError : public SystemError
  {
  public:
    NativeWindowInUseKHRError( std::string const & message ) : SystemError( make_error_code( Result::eErrorNativeWindowInUseKHR ), message ) {}

    NativeWindowInUseKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorNativeWindowInUseKHR ), message ) {}
  };

  class OutOfDateKHRError : public SystemError
  {
  public:
    OutOfDateKHRError( std::string const & message ) : SystemError( make_error_code( Result::eErrorOutOfDateKHR ), message ) {}

    OutOfDateKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorOutOfDateKHR ), message ) {}
  };

  class IncompatibleDisplayKHRError : public SystemError
  {
  public:
    IncompatibleDisplayKHRError( std::string const & message ) : SystemError( make_error_code( Result::eErrorIncompatibleDisplayKHR ), message ) {}

    IncompatibleDisplayKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorIncompatibleDisplayKHR ), message ) {}
  };

  class InvalidShaderNVError : public SystemError
  {
  public:
    InvalidShaderNVError( std::string const & message ) : SystemError( make_error_code( Result::eErrorInvalidShaderNV ), message ) {}

    InvalidShaderNVError( char const * message ) : SystemError( make_error_code( Result::eErrorInvalidShaderNV ), message ) {}
  };

  class ImageUsageNotSupportedKHRError : public SystemError
  {
  public:
    ImageUsageNotSupportedKHRError( std::string const & message ) : SystemError( make_error_code( Result::eErrorImageUsageNotSupportedKHR ), message ) {}

    ImageUsageNotSupportedKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorImageUsageNotSupportedKHR ), message ) {}
  };

  class VideoPictureLayoutNotSupportedKHRError : public SystemError
  {
  public:
    VideoPictureLayoutNotSupportedKHRError( std::string const & message )
      : SystemError( make_error_code( Result::eErrorVideoPictureLayoutNotSupportedKHR ), message )
    {
    }

    VideoPictureLayoutNotSupportedKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorVideoPictureLayoutNotSupportedKHR ), message )
    {
    }
  };

  class VideoProfileOperationNotSupportedKHRError : public SystemError
  {
  public:
    VideoProfileOperationNotSupportedKHRError( std::string const & message )
      : SystemError( make_error_code( Result::eErrorVideoProfileOperationNotSupportedKHR ), message )
    {
    }

    VideoProfileOperationNotSupportedKHRError( char const * message )
      : SystemError( make_error_code( Result::eErrorVideoProfileOperationNotSupportedKHR ), message )
    {
    }
  };

  class VideoProfileFormatNotSupportedKHRError : public SystemError
  {
  public:
    VideoProfileFormatNotSupportedKHRError( std::string const & message )
      : SystemError( make_error_code( Result::eErrorVideoProfileFormatNotSupportedKHR ), message )
    {
    }

    VideoProfileFormatNotSupportedKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorVideoProfileFormatNotSupportedKHR ), message )
    {
    }
  };

  class VideoProfileCodecNotSupportedKHRError : public SystemError
  {
  public:
    VideoProfileCodecNotSupportedKHRError( std::string const & message )
      : SystemError( make_error_code( Result::eErrorVideoProfileCodecNotSupportedKHR ), message )
    {
    }

    VideoProfileCodecNotSupportedKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorVideoProfileCodecNotSupportedKHR ), message ) {}
  };

  class VideoStdVersionNotSupportedKHRError : public SystemError
  {
  public:
    VideoStdVersionNotSupportedKHRError( std::string const & message ) : SystemError( make_error_code( Result::eErrorVideoStdVersionNotSupportedKHR ), message )
    {
    }

    VideoStdVersionNotSupportedKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorVideoStdVersionNotSupportedKHR ), message ) {}
  };

  class InvalidDrmFormatModifierPlaneLayoutEXTError : public SystemError
  {
  public:
    InvalidDrmFormatModifierPlaneLayoutEXTError( std::string const & message )
      : SystemError( make_error_code( Result::eErrorInvalidDrmFormatModifierPlaneLayoutEXT ), message )
    {
    }

    InvalidDrmFormatModifierPlaneLayoutEXTError( char const * message )
      : SystemError( make_error_code( Result::eErrorInvalidDrmFormatModifierPlaneLayoutEXT ), message )
    {
    }
  };

  class PresentTimingQueueFullEXTError : public SystemError
  {
  public:
    PresentTimingQueueFullEXTError( std::string const & message ) : SystemError( make_error_code( Result::eErrorPresentTimingQueueFullEXT ), message ) {}

    PresentTimingQueueFullEXTError( char const * message ) : SystemError( make_error_code( Result::eErrorPresentTimingQueueFullEXT ), message ) {}
  };

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
  class FullScreenExclusiveModeLostEXTError : public SystemError
  {
  public:
    FullScreenExclusiveModeLostEXTError( std::string const & message ) : SystemError( make_error_code( Result::eErrorFullScreenExclusiveModeLostEXT ), message )
    {
    }

    FullScreenExclusiveModeLostEXTError( char const * message ) : SystemError( make_error_code( Result::eErrorFullScreenExclusiveModeLostEXT ), message ) {}
  };
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

  class InvalidVideoStdParametersKHRError : public SystemError
  {
  public:
    InvalidVideoStdParametersKHRError( std::string const & message ) : SystemError( make_error_code( Result::eErrorInvalidVideoStdParametersKHR ), message ) {}

    InvalidVideoStdParametersKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorInvalidVideoStdParametersKHR ), message ) {}
  };

  class CompressionExhaustedEXTError : public SystemError
  {
  public:
    CompressionExhaustedEXTError( std::string const & message ) : SystemError( make_error_code( Result::eErrorCompressionExhaustedEXT ), message ) {}

    CompressionExhaustedEXTError( char const * message ) : SystemError( make_error_code( Result::eErrorCompressionExhaustedEXT ), message ) {}
  };

  class NotEnoughSpaceKHRError : public SystemError
  {
  public:
    NotEnoughSpaceKHRError( std::string const & message ) : SystemError( make_error_code( Result::eErrorNotEnoughSpaceKHR ), message ) {}

    NotEnoughSpaceKHRError( char const * message ) : SystemError( make_error_code( Result::eErrorNotEnoughSpaceKHR ), message ) {}
  };

  namespace detail
  {
    [[noreturn]] VULKAN_HPP_INLINE void throwResultException( Result result, char const * message )
    {
      switch ( result )
      {
        case Result::eErrorOutOfHostMemory                       : throw OutOfHostMemoryError( message );
        case Result::eErrorOutOfDeviceMemory                     : throw OutOfDeviceMemoryError( message );
        case Result::eErrorInitializationFailed                  : throw InitializationFailedError( message );
        case Result::eErrorDeviceLost                            : throw DeviceLostError( message );
        case Result::eErrorMemoryMapFailed                       : throw MemoryMapFailedError( message );
        case Result::eErrorLayerNotPresent                       : throw LayerNotPresentError( message );
        case Result::eErrorExtensionNotPresent                   : throw ExtensionNotPresentError( message );
        case Result::eErrorFeatureNotPresent                     : throw FeatureNotPresentError( message );
        case Result::eErrorIncompatibleDriver                    : throw IncompatibleDriverError( message );
        case Result::eErrorTooManyObjects                        : throw TooManyObjectsError( message );
        case Result::eErrorFormatNotSupported                    : throw FormatNotSupportedError( message );
        case Result::eErrorFragmentedPool                        : throw FragmentedPoolError( message );
        case Result::eErrorUnknown                               : throw UnknownError( message );
        case Result::eErrorValidationFailed                      : throw ValidationFailedError( message );
        case Result::eErrorOutOfPoolMemory                       : throw OutOfPoolMemoryError( message );
        case Result::eErrorInvalidExternalHandle                 : throw InvalidExternalHandleError( message );
        case Result::eErrorInvalidOpaqueCaptureAddress           : throw InvalidOpaqueCaptureAddressError( message );
        case Result::eErrorFragmentation                         : throw FragmentationError( message );
        case Result::eErrorNotPermitted                          : throw NotPermittedError( message );
        case Result::eErrorSurfaceLostKHR                        : throw SurfaceLostKHRError( message );
        case Result::eErrorNativeWindowInUseKHR                  : throw NativeWindowInUseKHRError( message );
        case Result::eErrorOutOfDateKHR                          : throw OutOfDateKHRError( message );
        case Result::eErrorIncompatibleDisplayKHR                : throw IncompatibleDisplayKHRError( message );
        case Result::eErrorInvalidShaderNV                       : throw InvalidShaderNVError( message );
        case Result::eErrorImageUsageNotSupportedKHR             : throw ImageUsageNotSupportedKHRError( message );
        case Result::eErrorVideoPictureLayoutNotSupportedKHR     : throw VideoPictureLayoutNotSupportedKHRError( message );
        case Result::eErrorVideoProfileOperationNotSupportedKHR  : throw VideoProfileOperationNotSupportedKHRError( message );
        case Result::eErrorVideoProfileFormatNotSupportedKHR     : throw VideoProfileFormatNotSupportedKHRError( message );
        case Result::eErrorVideoProfileCodecNotSupportedKHR      : throw VideoProfileCodecNotSupportedKHRError( message );
        case Result::eErrorVideoStdVersionNotSupportedKHR        : throw VideoStdVersionNotSupportedKHRError( message );
        case Result::eErrorInvalidDrmFormatModifierPlaneLayoutEXT: throw InvalidDrmFormatModifierPlaneLayoutEXTError( message );
        case Result::eErrorPresentTimingQueueFullEXT             : throw PresentTimingQueueFullEXTError( message );
#  if defined( VK_USE_PLATFORM_WIN32_KHR )
        case Result::eErrorFullScreenExclusiveModeLostEXT: throw FullScreenExclusiveModeLostEXTError( message );
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/
        case Result::eErrorInvalidVideoStdParametersKHR: throw InvalidVideoStdParametersKHRError( message );
        case Result::eErrorCompressionExhaustedEXT     : throw CompressionExhaustedEXTError( message );
        case Result::eErrorNotEnoughSpaceKHR           : throw NotEnoughSpaceKHRError( message );
        default                                        : throw SystemError( make_error_code( result ), message );
      }
    }
  }  // namespace detail
#endif

  template <typename T>
  struct ResultValue
  {
#ifdef VULKAN_HPP_HAS_NOEXCEPT
    ResultValue( Result r, T & v ) VULKAN_HPP_NOEXCEPT( VULKAN_HPP_NOEXCEPT( T( v ) ) )
#else
    ResultValue( Result r, T & v )
#endif
      : result( r ), value( v )
    {
    }

#ifdef VULKAN_HPP_HAS_NOEXCEPT
    ResultValue( Result r, T && v ) VULKAN_HPP_NOEXCEPT( VULKAN_HPP_NOEXCEPT( T( std::move( v ) ) ) )
#else
    ResultValue( Result r, T && v )
#endif
      : result( r ), value( std::move( v ) )
    {
    }

    Result result;
    T      value;

    operator std::tuple<Result &, T &>() VULKAN_HPP_NOEXCEPT
    {
      return std::tuple<Result &, T &>( result, value );
    }

    std::tuple<Result, T> asTuple() &&
    {
      return std::make_tuple( result, std::move( value ) );
    }

    // std::expected-look alike
    bool has_value() const VULKAN_HPP_NOEXCEPT
    {
      return result == vk::Result::eSuccess;
    }

    T const * operator->() const VULKAN_HPP_NOEXCEPT
    {
      VULKAN_HPP_ASSERT( has_value() );
      return &value;
    }

    T * operator->() VULKAN_HPP_NOEXCEPT
    {
      VULKAN_HPP_ASSERT( has_value() );
      return &value;
    }

    T const & operator*() const VULKAN_HPP_NOEXCEPT
    {
      VULKAN_HPP_ASSERT( has_value() );
      return value;
    }

    T & operator*() VULKAN_HPP_NOEXCEPT
    {
      VULKAN_HPP_ASSERT( has_value() );
      return value;
    }
  };

  template <typename T>
  struct ResultValueType
  {
#ifdef VULKAN_HPP_NO_EXCEPTIONS
#  ifdef VULKAN_HPP_EXPECTED
    using type = VULKAN_HPP_EXPECTED<T, Result>;
#  else
    using type = ResultValue<T>;
#  endif
#else
    using type = T;
#endif
  };

  template <>
  struct ResultValueType<void>
  {
#ifdef VULKAN_HPP_NO_EXCEPTIONS
#  ifdef VULKAN_HPP_EXPECTED
    using type = VULKAN_HPP_EXPECTED<void, Result>;
#  else
    using type = Result;
#  endif
#else
    using type = void;
#endif
  };

  namespace detail
  {
    template <typename T>
    VULKAN_HPP_CONSTEXPR bool ignore( T const & ) VULKAN_HPP_NOEXCEPT
    {
      return true;
    }

    VULKAN_HPP_INLINE typename ResultValueType<void>::type createResultValueType( Result result )
    {
#if defined( VULKAN_HPP_NO_EXCEPTIONS )
#  ifdef VULKAN_HPP_UNEXPECTED
      if ( result == Result::eSuccess )
      {
        return {};
      }
      return VULKAN_HPP_UNEXPECTED( result );
#  else
      return result;
#  endif
#else
      ignore( result );
#endif
    }

    template <typename T>
    VULKAN_HPP_INLINE typename ResultValueType<T>::type createResultValueType( Result result, T & data )
    {
#if defined( VULKAN_HPP_NO_EXCEPTIONS )
#  ifdef VULKAN_HPP_EXPECTED
      if ( result == Result::eSuccess )
      {
        return data;
      }
      return VULKAN_HPP_UNEXPECTED( result );
#  else
      return ResultValue<T>( result, data );
#  endif
#else
      ignore( result );
      return data;
#endif
    }

    template <typename T>
    VULKAN_HPP_INLINE typename ResultValueType<T>::type createResultValueType( Result result, T && data )
    {
#if defined( VULKAN_HPP_NO_EXCEPTIONS )
#  ifdef VULKAN_HPP_EXPECTED
      if ( result == Result::eSuccess )
      {
        return std::move( data );
      }
      return VULKAN_HPP_UNEXPECTED( result );
#  else
      return ResultValue<T>( result, std::move( data ) );
#  endif
#else
      ignore( result );
      return std::move( data );
#endif
    }
  }  // namespace detail

  namespace detail
  {
    VULKAN_HPP_INLINE void resultCheck( Result result, char const * message )
    {
#ifdef VULKAN_HPP_NO_EXCEPTIONS
      ignore( result );  // just in case VULKAN_HPP_ASSERT_ON_RESULT is empty
      ignore( message );
      VULKAN_HPP_ASSERT_ON_RESULT( result == Result::eSuccess );
#else
      if ( result != Result::eSuccess )
      {
        throwResultException( result, message );
      }
#endif
    }

    VULKAN_HPP_INLINE void resultCheck( Result result, char const * message, std::initializer_list<Result> successCodes )
    {
#ifdef VULKAN_HPP_NO_EXCEPTIONS
      ignore( result );  // just in case VULKAN_HPP_ASSERT_ON_RESULT is empty
      ignore( message );
      ignore( successCodes );  // just in case VULKAN_HPP_ASSERT_ON_RESULT is empty
      VULKAN_HPP_ASSERT_ON_RESULT( std::find( successCodes.begin(), successCodes.end(), result ) != successCodes.end() );
#else
      if ( std::find( successCodes.begin(), successCodes.end(), result ) == successCodes.end() )
      {
        throwResultException( result, message );
      }
#endif
    }

    template <typename HandleType, typename AllocatorType, typename Dispatch>
    VULKAN_HPP_INLINE void resultCheck( Result                                         result,
                                        char const *                                   message,
                                        std::initializer_list<Result>                  successCodes,
                                        VkDevice                                       device,
                                        std::vector<HandleType, AllocatorType> const & pipelines,
                                        AllocationCallbacks const *                    pAllocator,
                                        Dispatch const &                               d )
    {
#ifdef VULKAN_HPP_NO_EXCEPTIONS
      ignore( result );  // just in case VULKAN_HPP_ASSERT_ON_RESULT is empty
      ignore( message );
      ignore( successCodes );  // just in case VULKAN_HPP_ASSERT_ON_RESULT is empty
      ignore( device );
      ignore( pipelines );
      ignore( pAllocator );
      ignore( d );
      VULKAN_HPP_ASSERT_ON_RESULT( std::find( successCodes.begin(), successCodes.end(), result ) != successCodes.end() );
#else
      if ( std::find( successCodes.begin(), successCodes.end(), result ) == successCodes.end() )
      {
        for ( HandleType pipeline : pipelines )
        {
          d.vkDestroyPipeline( device, static_cast<VkPipeline>( pipeline ), reinterpret_cast<VkAllocationCallbacks const *>( pAllocator ) );
        }
        throwResultException( result, message );
      }
#endif
    }
  }  // namespace detail

  //===========================
  //=== CONSTEXPR CONSTANTs ===
  //===========================

  //=== VK_VERSION_1_0 ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t False                     = VK_FALSE;
  VULKAN_HPP_CONSTEXPR_INLINE float    LodClampNone              = VK_LOD_CLAMP_NONE;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t QueueFamilyIgnored        = VK_QUEUE_FAMILY_IGNORED;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t RemainingArrayLayers      = VK_REMAINING_ARRAY_LAYERS;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t RemainingMipLevels        = VK_REMAINING_MIP_LEVELS;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t True                      = VK_TRUE;
  VULKAN_HPP_CONSTEXPR_INLINE uint64_t WholeSize                 = VK_WHOLE_SIZE;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxMemoryTypes            = VK_MAX_MEMORY_TYPES;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxPhysicalDeviceNameSize = VK_MAX_PHYSICAL_DEVICE_NAME_SIZE;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t UuidSize                  = VK_UUID_SIZE;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxExtensionNameSize      = VK_MAX_EXTENSION_NAME_SIZE;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxDescriptionSize        = VK_MAX_DESCRIPTION_SIZE;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxMemoryHeaps            = VK_MAX_MEMORY_HEAPS;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t AttachmentUnused          = VK_ATTACHMENT_UNUSED;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t SubpassExternal           = VK_SUBPASS_EXTERNAL;

  //=== VK_VERSION_1_1 ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxDeviceGroupSize  = VK_MAX_DEVICE_GROUP_SIZE;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t LuidSize            = VK_LUID_SIZE;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t QueueFamilyExternal = VK_QUEUE_FAMILY_EXTERNAL;

  //=== VK_VERSION_1_2 ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxDriverNameSize = VK_MAX_DRIVER_NAME_SIZE;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxDriverInfoSize = VK_MAX_DRIVER_INFO_SIZE;

  //=== VK_VERSION_1_4 ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxGlobalPrioritySize = VK_MAX_GLOBAL_PRIORITY_SIZE;

  //=== VK_KHR_device_group_creation ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxDeviceGroupSizeKHR = VK_MAX_DEVICE_GROUP_SIZE_KHR;

  //=== VK_KHR_external_memory_capabilities ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t LuidSizeKHR = VK_LUID_SIZE_KHR;

  //=== VK_KHR_external_memory ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t QueueFamilyExternalKHR = VK_QUEUE_FAMILY_EXTERNAL_KHR;

  //=== VK_EXT_queue_family_foreign ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t QueueFamilyForeignEXT = VK_QUEUE_FAMILY_FOREIGN_EXT;

#if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_AMDX_shader_enqueue ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t ShaderIndexUnusedAMDX = VK_SHADER_INDEX_UNUSED_AMDX;
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_KHR_ray_tracing_pipeline ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t ShaderUnusedKHR = VK_SHADER_UNUSED_KHR;

  //=== VK_NV_ray_tracing ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t ShaderUnusedNV = VK_SHADER_UNUSED_NV;

  //=== VK_KHR_global_priority ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxGlobalPrioritySizeKHR = VK_MAX_GLOBAL_PRIORITY_SIZE_KHR;

  //=== VK_KHR_driver_properties ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxDriverNameSizeKHR = VK_MAX_DRIVER_NAME_SIZE_KHR;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxDriverInfoSizeKHR = VK_MAX_DRIVER_INFO_SIZE_KHR;

  //=== VK_EXT_global_priority_query ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxGlobalPrioritySizeEXT = VK_MAX_GLOBAL_PRIORITY_SIZE_EXT;

  //=== VK_EXT_image_sliced_view_of_3d ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t Remaining3DSlicesEXT = VK_REMAINING_3D_SLICES_EXT;

  //=== VK_EXT_shader_module_identifier ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxShaderModuleIdentifierSizeEXT = VK_MAX_SHADER_MODULE_IDENTIFIER_SIZE_EXT;

#if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_AMDX_dense_geometry_format ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t CompressedTriangleFormatDgf1ByteAlignmentAMDX = VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_ALIGNMENT_AMDX;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t CompressedTriangleFormatDgf1ByteStrideAMDX    = VK_COMPRESSED_TRIANGLE_FORMAT_DGF1_BYTE_STRIDE_AMDX;
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_KHR_pipeline_binary ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxPipelineBinaryKeySizeKHR = VK_MAX_PIPELINE_BINARY_KEY_SIZE_KHR;

  //=== VK_ARM_data_graph ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxPhysicalDeviceDataGraphOperationSetNameSizeARM = VK_MAX_PHYSICAL_DEVICE_DATA_GRAPH_OPERATION_SET_NAME_SIZE_ARM;

  //=== VK_ARM_data_graph_instruction_set_tosa ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxDataGraphTosaNameSizeARM = VK_MAX_DATA_GRAPH_TOSA_NAME_SIZE_ARM;

  //=== VK_KHR_video_decode_av1 ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxVideoAv1ReferencesPerFrameKHR = VK_MAX_VIDEO_AV1_REFERENCES_PER_FRAME_KHR;

  //=== VK_KHR_video_decode_vp9 ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t MaxVideoVp9ReferencesPerFrameKHR = VK_MAX_VIDEO_VP9_REFERENCES_PER_FRAME_KHR;

  //=== VK_NV_partitioned_acceleration_structure ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t PartitionedAccelerationStructurePartitionIndexGlobalNV = VK_PARTITIONED_ACCELERATION_STRUCTURE_PARTITION_INDEX_GLOBAL_NV;

  //=== VK_QCOM_data_graph_model ===
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t DataGraphModelToolchainVersionLengthQCOM = VK_DATA_GRAPH_MODEL_TOOLCHAIN_VERSION_LENGTH_QCOM;

  //=== VK_NV_compute_occupancy_priority ===
  VULKAN_HPP_CONSTEXPR_INLINE float ComputeOccupancyPriorityLowNV    = VK_COMPUTE_OCCUPANCY_PRIORITY_LOW_NV;
  VULKAN_HPP_CONSTEXPR_INLINE float ComputeOccupancyPriorityNormalNV = VK_COMPUTE_OCCUPANCY_PRIORITY_NORMAL_NV;
  VULKAN_HPP_CONSTEXPR_INLINE float ComputeOccupancyPriorityHighNV   = VK_COMPUTE_OCCUPANCY_PRIORITY_HIGH_NV;

  //========================
  //=== CONSTEXPR VALUEs ===
  //========================
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t HeaderVersion      = VK_HEADER_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE uint32_t Use64BitPtrDefines = VK_USE_64_BIT_PTR_DEFINES;

  //=========================
  //=== CONSTEXPR CALLEEs ===
  //=========================
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
  VULKAN_HPP_CONSTEXPR uint32_t apiVersionMajor( T const version )
  {
    return ( ( (uint32_t)( version ) >> 22U ) & 0x7FU );
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
  VULKAN_HPP_CONSTEXPR uint32_t apiVersionMinor( T const version )
  {
    return ( ( (uint32_t)( version ) >> 12U ) & 0x3FFU );
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
  VULKAN_HPP_CONSTEXPR uint32_t apiVersionPatch( T const version )
  {
    return ( (uint32_t)( version ) & 0xFFFU );
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
  VULKAN_HPP_CONSTEXPR uint32_t apiVersionVariant( T const version )
  {
    return ( (uint32_t)( version ) >> 29U );
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
  VULKAN_HPP_CONSTEXPR uint32_t makeApiVersion( T const variant, T const major, T const minor, T const patch )
  {
    return ( ( ( (uint32_t)( variant ) ) << 29U ) | ( ( (uint32_t)( major ) ) << 22U ) | ( ( (uint32_t)( minor ) ) << 12U ) | ( (uint32_t)( patch ) ) );
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
  VULKAN_HPP_CONSTEXPR uint32_t makeVersion( T const major, T const minor, T const patch )
  {
    return ( ( ( (uint32_t)( major ) ) << 22U ) | ( ( (uint32_t)( minor ) ) << 12U ) | ( (uint32_t)( patch ) ) );
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
  VULKAN_HPP_CONSTEXPR uint32_t versionMajor( T const version )
  {
    return ( (uint32_t)( version ) >> 22U );
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
  VULKAN_HPP_CONSTEXPR uint32_t versionMinor( T const version )
  {
    return ( ( (uint32_t)( version ) >> 12U ) & 0x3FFU );
  }
  template <typename T, typename = typename std::enable_if<std::is_integral<T>::value>::type>
  VULKAN_HPP_CONSTEXPR uint32_t versionPatch( T const version )
  {
    return ( (uint32_t)( version ) & 0xFFFU );
  }

  //=========================
  //=== CONSTEXPR CALLERs ===
  //=========================
  VULKAN_HPP_CONSTEXPR_INLINE auto ApiVersion            = makeApiVersion( 0, 1, 0, 0 );
  VULKAN_HPP_CONSTEXPR_INLINE auto ApiVersion10          = makeApiVersion( 0, 1, 0, 0 );
  VULKAN_HPP_CONSTEXPR_INLINE auto ApiVersion11          = makeApiVersion( 0, 1, 1, 0 );
  VULKAN_HPP_CONSTEXPR_INLINE auto ApiVersion12          = makeApiVersion( 0, 1, 2, 0 );
  VULKAN_HPP_CONSTEXPR_INLINE auto ApiVersion13          = makeApiVersion( 0, 1, 3, 0 );
  VULKAN_HPP_CONSTEXPR_INLINE auto ApiVersion14          = makeApiVersion( 0, 1, 4, 0 );
  VULKAN_HPP_CONSTEXPR_INLINE auto HeaderVersionComplete = makeApiVersion( 0, 1, 4, VK_HEADER_VERSION );

  //=================================
  //=== CONSTEXPR EXTENSION NAMEs ===
  //=================================

  //=== VK_KHR_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSurfaceSpecVersion   = VK_KHR_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSurfaceExtensionName = VK_KHR_SURFACE_EXTENSION_NAME;

  //=== VK_KHR_swapchain ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSwapchainSpecVersion   = VK_KHR_SWAPCHAIN_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSwapchainExtensionName = VK_KHR_SWAPCHAIN_EXTENSION_NAME;

  //=== VK_KHR_display ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDisplaySpecVersion   = VK_KHR_DISPLAY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDisplayExtensionName = VK_KHR_DISPLAY_EXTENSION_NAME;

  //=== VK_KHR_display_swapchain ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDisplaySwapchainSpecVersion   = VK_KHR_DISPLAY_SWAPCHAIN_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDisplaySwapchainExtensionName = VK_KHR_DISPLAY_SWAPCHAIN_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_XLIB_KHR )
  //=== VK_KHR_xlib_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRXlibSurfaceSpecVersion   = VK_KHR_XLIB_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRXlibSurfaceExtensionName = VK_KHR_XLIB_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_XLIB_KHR*/

#if defined( VK_USE_PLATFORM_XCB_KHR )
  //=== VK_KHR_xcb_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRXcbSurfaceSpecVersion   = VK_KHR_XCB_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRXcbSurfaceExtensionName = VK_KHR_XCB_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_XCB_KHR*/

#if defined( VK_USE_PLATFORM_WAYLAND_KHR )
  //=== VK_KHR_wayland_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRWaylandSurfaceSpecVersion   = VK_KHR_WAYLAND_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRWaylandSurfaceExtensionName = VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_WAYLAND_KHR*/

#if defined( VK_USE_PLATFORM_ANDROID_KHR )
  //=== VK_KHR_android_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRAndroidSurfaceSpecVersion   = VK_KHR_ANDROID_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRAndroidSurfaceExtensionName = VK_KHR_ANDROID_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_ANDROID_KHR*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_win32_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRWin32SurfaceSpecVersion   = VK_KHR_WIN32_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRWin32SurfaceExtensionName = VK_KHR_WIN32_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_EXT_debug_report ===
  VULKAN_HPP_DEPRECATED( "The VK_EXT_debug_report extension has been deprecated by VK_EXT_debug_utils." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDebugReportSpecVersion = VK_EXT_DEBUG_REPORT_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_EXT_debug_report extension has been deprecated by VK_EXT_debug_utils." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDebugReportExtensionName = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;

  //=== VK_NV_glsl_shader ===
  VULKAN_HPP_DEPRECATED( "The VK_NV_glsl_shader extension has been deprecated." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVGlslShaderSpecVersion = VK_NV_GLSL_SHADER_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_NV_glsl_shader extension has been deprecated." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVGlslShaderExtensionName = VK_NV_GLSL_SHADER_EXTENSION_NAME;

  //=== VK_EXT_depth_range_unrestricted ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthRangeUnrestrictedSpecVersion   = VK_EXT_DEPTH_RANGE_UNRESTRICTED_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthRangeUnrestrictedExtensionName = VK_EXT_DEPTH_RANGE_UNRESTRICTED_EXTENSION_NAME;

  //=== VK_KHR_sampler_mirror_clamp_to_edge ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSamplerMirrorClampToEdgeSpecVersion   = VK_KHR_SAMPLER_MIRROR_CLAMP_TO_EDGE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSamplerMirrorClampToEdgeExtensionName = VK_KHR_SAMPLER_MIRROR_CLAMP_TO_EDGE_EXTENSION_NAME;

  //=== VK_IMG_filter_cubic ===
  VULKAN_HPP_CONSTEXPR_INLINE auto IMGFilterCubicSpecVersion   = VK_IMG_FILTER_CUBIC_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto IMGFilterCubicExtensionName = VK_IMG_FILTER_CUBIC_EXTENSION_NAME;

  //=== VK_AMD_rasterization_order ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDRasterizationOrderSpecVersion   = VK_AMD_RASTERIZATION_ORDER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDRasterizationOrderExtensionName = VK_AMD_RASTERIZATION_ORDER_EXTENSION_NAME;

  //=== VK_AMD_shader_trinary_minmax ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderTrinaryMinmaxSpecVersion   = VK_AMD_SHADER_TRINARY_MINMAX_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderTrinaryMinmaxExtensionName = VK_AMD_SHADER_TRINARY_MINMAX_EXTENSION_NAME;

  //=== VK_AMD_shader_explicit_vertex_parameter ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderExplicitVertexParameterSpecVersion   = VK_AMD_SHADER_EXPLICIT_VERTEX_PARAMETER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderExplicitVertexParameterExtensionName = VK_AMD_SHADER_EXPLICIT_VERTEX_PARAMETER_EXTENSION_NAME;

  //=== VK_EXT_debug_marker ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDebugMarkerSpecVersion   = VK_EXT_DEBUG_MARKER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDebugMarkerExtensionName = VK_EXT_DEBUG_MARKER_EXTENSION_NAME;

  //=== VK_KHR_video_queue ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoQueueSpecVersion   = VK_KHR_VIDEO_QUEUE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoQueueExtensionName = VK_KHR_VIDEO_QUEUE_EXTENSION_NAME;

  //=== VK_KHR_video_decode_queue ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoDecodeQueueSpecVersion   = VK_KHR_VIDEO_DECODE_QUEUE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoDecodeQueueExtensionName = VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME;

  //=== VK_AMD_gcn_shader ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDGcnShaderSpecVersion   = VK_AMD_GCN_SHADER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDGcnShaderExtensionName = VK_AMD_GCN_SHADER_EXTENSION_NAME;

  //=== VK_NV_dedicated_allocation ===
  VULKAN_HPP_DEPRECATED( "The VK_NV_dedicated_allocation extension has been deprecated by VK_KHR_dedicated_allocation." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDedicatedAllocationSpecVersion = VK_NV_DEDICATED_ALLOCATION_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_NV_dedicated_allocation extension has been deprecated by VK_KHR_dedicated_allocation." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDedicatedAllocationExtensionName = VK_NV_DEDICATED_ALLOCATION_EXTENSION_NAME;

  //=== VK_EXT_transform_feedback ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTTransformFeedbackSpecVersion   = VK_EXT_TRANSFORM_FEEDBACK_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTTransformFeedbackExtensionName = VK_EXT_TRANSFORM_FEEDBACK_EXTENSION_NAME;

  //=== VK_NVX_binary_import ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVXBinaryImportSpecVersion   = VK_NVX_BINARY_IMPORT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVXBinaryImportExtensionName = VK_NVX_BINARY_IMPORT_EXTENSION_NAME;

  //=== VK_NVX_image_view_handle ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVXImageViewHandleSpecVersion   = VK_NVX_IMAGE_VIEW_HANDLE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVXImageViewHandleExtensionName = VK_NVX_IMAGE_VIEW_HANDLE_EXTENSION_NAME;

  //=== VK_AMD_draw_indirect_count ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDDrawIndirectCountSpecVersion   = VK_AMD_DRAW_INDIRECT_COUNT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDDrawIndirectCountExtensionName = VK_AMD_DRAW_INDIRECT_COUNT_EXTENSION_NAME;

  //=== VK_AMD_negative_viewport_height ===
  VULKAN_HPP_DEPRECATED( "The VK_AMD_negative_viewport_height extension has been obsoleted by VK_KHR_maintenance1." )
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDNegativeViewportHeightSpecVersion = VK_AMD_NEGATIVE_VIEWPORT_HEIGHT_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_AMD_negative_viewport_height extension has been obsoleted by VK_KHR_maintenance1." )
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDNegativeViewportHeightExtensionName = VK_AMD_NEGATIVE_VIEWPORT_HEIGHT_EXTENSION_NAME;

  //=== VK_AMD_gpu_shader_half_float ===
  VULKAN_HPP_DEPRECATED( "The VK_AMD_gpu_shader_half_float extension has been deprecated by VK_KHR_shader_float16_int8." )
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDGpuShaderHalfFloatSpecVersion = VK_AMD_GPU_SHADER_HALF_FLOAT_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_AMD_gpu_shader_half_float extension has been deprecated by VK_KHR_shader_float16_int8." )
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDGpuShaderHalfFloatExtensionName = VK_AMD_GPU_SHADER_HALF_FLOAT_EXTENSION_NAME;

  //=== VK_AMD_shader_ballot ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderBallotSpecVersion   = VK_AMD_SHADER_BALLOT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderBallotExtensionName = VK_AMD_SHADER_BALLOT_EXTENSION_NAME;

  //=== VK_KHR_video_encode_h264 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeH264SpecVersion   = VK_KHR_VIDEO_ENCODE_H264_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeH264ExtensionName = VK_KHR_VIDEO_ENCODE_H264_EXTENSION_NAME;

  //=== VK_KHR_video_encode_h265 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeH265SpecVersion   = VK_KHR_VIDEO_ENCODE_H265_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeH265ExtensionName = VK_KHR_VIDEO_ENCODE_H265_EXTENSION_NAME;

  //=== VK_KHR_video_decode_h264 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoDecodeH264SpecVersion   = VK_KHR_VIDEO_DECODE_H264_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoDecodeH264ExtensionName = VK_KHR_VIDEO_DECODE_H264_EXTENSION_NAME;

  //=== VK_AMD_texture_gather_bias_lod ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDTextureGatherBiasLodSpecVersion   = VK_AMD_TEXTURE_GATHER_BIAS_LOD_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDTextureGatherBiasLodExtensionName = VK_AMD_TEXTURE_GATHER_BIAS_LOD_EXTENSION_NAME;

  //=== VK_AMD_shader_info ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderInfoSpecVersion   = VK_AMD_SHADER_INFO_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderInfoExtensionName = VK_AMD_SHADER_INFO_EXTENSION_NAME;

  //=== VK_KHR_dynamic_rendering ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDynamicRenderingSpecVersion   = VK_KHR_DYNAMIC_RENDERING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDynamicRenderingExtensionName = VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME;

  //=== VK_AMD_shader_image_load_store_lod ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderImageLoadStoreLodSpecVersion   = VK_AMD_SHADER_IMAGE_LOAD_STORE_LOD_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderImageLoadStoreLodExtensionName = VK_AMD_SHADER_IMAGE_LOAD_STORE_LOD_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_GGP )
  //=== VK_GGP_stream_descriptor_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto GGPStreamDescriptorSurfaceSpecVersion   = VK_GGP_STREAM_DESCRIPTOR_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto GGPStreamDescriptorSurfaceExtensionName = VK_GGP_STREAM_DESCRIPTOR_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_GGP*/

  //=== VK_NV_corner_sampled_image ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCornerSampledImageSpecVersion   = VK_NV_CORNER_SAMPLED_IMAGE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCornerSampledImageExtensionName = VK_NV_CORNER_SAMPLED_IMAGE_EXTENSION_NAME;

  //=== VK_KHR_multiview ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMultiviewSpecVersion   = VK_KHR_MULTIVIEW_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMultiviewExtensionName = VK_KHR_MULTIVIEW_EXTENSION_NAME;

  //=== VK_IMG_format_pvrtc ===
  VULKAN_HPP_DEPRECATED( "The VK_IMG_format_pvrtc extension has been deprecated." )
  VULKAN_HPP_CONSTEXPR_INLINE auto IMGFormatPvrtcSpecVersion = VK_IMG_FORMAT_PVRTC_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_IMG_format_pvrtc extension has been deprecated." )
  VULKAN_HPP_CONSTEXPR_INLINE auto IMGFormatPvrtcExtensionName = VK_IMG_FORMAT_PVRTC_EXTENSION_NAME;

  //=== VK_NV_external_memory_capabilities ===
  VULKAN_HPP_DEPRECATED( "The VK_NV_external_memory_capabilities extension has been deprecated by VK_KHR_external_memory_capabilities." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExternalMemoryCapabilitiesSpecVersion = VK_NV_EXTERNAL_MEMORY_CAPABILITIES_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_NV_external_memory_capabilities extension has been deprecated by VK_KHR_external_memory_capabilities." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExternalMemoryCapabilitiesExtensionName = VK_NV_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME;

  //=== VK_NV_external_memory ===
  VULKAN_HPP_DEPRECATED( "The VK_NV_external_memory extension has been deprecated by VK_KHR_external_memory." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExternalMemorySpecVersion = VK_NV_EXTERNAL_MEMORY_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_NV_external_memory extension has been deprecated by VK_KHR_external_memory." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExternalMemoryExtensionName = VK_NV_EXTERNAL_MEMORY_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_NV_external_memory_win32 ===
  VULKAN_HPP_DEPRECATED( "The VK_NV_external_memory_win32 extension has been deprecated by VK_KHR_external_memory_win32." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExternalMemoryWin32SpecVersion = VK_NV_EXTERNAL_MEMORY_WIN32_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_NV_external_memory_win32 extension has been deprecated by VK_KHR_external_memory_win32." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExternalMemoryWin32ExtensionName = VK_NV_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_NV_win32_keyed_mutex ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVWin32KeyedMutexSpecVersion   = VK_NV_WIN32_KEYED_MUTEX_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVWin32KeyedMutexExtensionName = VK_NV_WIN32_KEYED_MUTEX_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_get_physical_device_properties2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRGetPhysicalDeviceProperties2SpecVersion   = VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRGetPhysicalDeviceProperties2ExtensionName = VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME;

  //=== VK_KHR_device_group ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDeviceGroupSpecVersion   = VK_KHR_DEVICE_GROUP_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDeviceGroupExtensionName = VK_KHR_DEVICE_GROUP_EXTENSION_NAME;

  //=== VK_EXT_validation_flags ===
  VULKAN_HPP_DEPRECATED( "The VK_EXT_validation_flags extension has been deprecated by VK_EXT_layer_settings." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTValidationFlagsSpecVersion = VK_EXT_VALIDATION_FLAGS_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_EXT_validation_flags extension has been deprecated by VK_EXT_layer_settings." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTValidationFlagsExtensionName = VK_EXT_VALIDATION_FLAGS_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_VI_NN )
  //=== VK_NN_vi_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NNViSurfaceSpecVersion   = VK_NN_VI_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NNViSurfaceExtensionName = VK_NN_VI_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_VI_NN*/

  //=== VK_KHR_shader_draw_parameters ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderDrawParametersSpecVersion   = VK_KHR_SHADER_DRAW_PARAMETERS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderDrawParametersExtensionName = VK_KHR_SHADER_DRAW_PARAMETERS_EXTENSION_NAME;

  //=== VK_EXT_shader_subgroup_ballot ===
  VULKAN_HPP_DEPRECATED( "The VK_EXT_shader_subgroup_ballot extension has been deprecated by VK_VERSION_1_2." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderSubgroupBallotSpecVersion = VK_EXT_SHADER_SUBGROUP_BALLOT_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_EXT_shader_subgroup_ballot extension has been deprecated by VK_VERSION_1_2." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderSubgroupBallotExtensionName = VK_EXT_SHADER_SUBGROUP_BALLOT_EXTENSION_NAME;

  //=== VK_EXT_shader_subgroup_vote ===
  VULKAN_HPP_DEPRECATED( "The VK_EXT_shader_subgroup_vote extension has been deprecated by VK_VERSION_1_1." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderSubgroupVoteSpecVersion = VK_EXT_SHADER_SUBGROUP_VOTE_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_EXT_shader_subgroup_vote extension has been deprecated by VK_VERSION_1_1." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderSubgroupVoteExtensionName = VK_EXT_SHADER_SUBGROUP_VOTE_EXTENSION_NAME;

  //=== VK_EXT_texture_compression_astc_hdr ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTTextureCompressionAstcHdrSpecVersion   = VK_EXT_TEXTURE_COMPRESSION_ASTC_HDR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTTextureCompressionAstcHdrExtensionName = VK_EXT_TEXTURE_COMPRESSION_ASTC_HDR_EXTENSION_NAME;

  //=== VK_EXT_astc_decode_mode ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTAstcDecodeModeSpecVersion   = VK_EXT_ASTC_DECODE_MODE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTAstcDecodeModeExtensionName = VK_EXT_ASTC_DECODE_MODE_EXTENSION_NAME;

  //=== VK_EXT_pipeline_robustness ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelineRobustnessSpecVersion   = VK_EXT_PIPELINE_ROBUSTNESS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelineRobustnessExtensionName = VK_EXT_PIPELINE_ROBUSTNESS_EXTENSION_NAME;

  //=== VK_KHR_maintenance1 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance1SpecVersion   = VK_KHR_MAINTENANCE_1_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance1ExtensionName = VK_KHR_MAINTENANCE_1_EXTENSION_NAME;

  //=== VK_KHR_device_group_creation ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDeviceGroupCreationSpecVersion   = VK_KHR_DEVICE_GROUP_CREATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDeviceGroupCreationExtensionName = VK_KHR_DEVICE_GROUP_CREATION_EXTENSION_NAME;

  //=== VK_KHR_external_memory_capabilities ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalMemoryCapabilitiesSpecVersion   = VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalMemoryCapabilitiesExtensionName = VK_KHR_EXTERNAL_MEMORY_CAPABILITIES_EXTENSION_NAME;

  //=== VK_KHR_external_memory ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalMemorySpecVersion   = VK_KHR_EXTERNAL_MEMORY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalMemoryExtensionName = VK_KHR_EXTERNAL_MEMORY_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_external_memory_win32 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalMemoryWin32SpecVersion   = VK_KHR_EXTERNAL_MEMORY_WIN32_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalMemoryWin32ExtensionName = VK_KHR_EXTERNAL_MEMORY_WIN32_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_external_memory_fd ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalMemoryFdSpecVersion   = VK_KHR_EXTERNAL_MEMORY_FD_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalMemoryFdExtensionName = VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_win32_keyed_mutex ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRWin32KeyedMutexSpecVersion   = VK_KHR_WIN32_KEYED_MUTEX_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRWin32KeyedMutexExtensionName = VK_KHR_WIN32_KEYED_MUTEX_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_external_semaphore_capabilities ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalSemaphoreCapabilitiesSpecVersion   = VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalSemaphoreCapabilitiesExtensionName = VK_KHR_EXTERNAL_SEMAPHORE_CAPABILITIES_EXTENSION_NAME;

  //=== VK_KHR_external_semaphore ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalSemaphoreSpecVersion   = VK_KHR_EXTERNAL_SEMAPHORE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalSemaphoreExtensionName = VK_KHR_EXTERNAL_SEMAPHORE_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_external_semaphore_win32 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalSemaphoreWin32SpecVersion   = VK_KHR_EXTERNAL_SEMAPHORE_WIN32_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalSemaphoreWin32ExtensionName = VK_KHR_EXTERNAL_SEMAPHORE_WIN32_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_external_semaphore_fd ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalSemaphoreFdSpecVersion   = VK_KHR_EXTERNAL_SEMAPHORE_FD_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalSemaphoreFdExtensionName = VK_KHR_EXTERNAL_SEMAPHORE_FD_EXTENSION_NAME;

  //=== VK_KHR_push_descriptor ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPushDescriptorSpecVersion   = VK_KHR_PUSH_DESCRIPTOR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPushDescriptorExtensionName = VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME;

  //=== VK_EXT_conditional_rendering ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTConditionalRenderingSpecVersion   = VK_EXT_CONDITIONAL_RENDERING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTConditionalRenderingExtensionName = VK_EXT_CONDITIONAL_RENDERING_EXTENSION_NAME;

  //=== VK_KHR_shader_float16_int8 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderFloat16Int8SpecVersion   = VK_KHR_SHADER_FLOAT16_INT8_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderFloat16Int8ExtensionName = VK_KHR_SHADER_FLOAT16_INT8_EXTENSION_NAME;

  //=== VK_KHR_16bit_storage ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHR16BitStorageSpecVersion   = VK_KHR_16BIT_STORAGE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHR16BitStorageExtensionName = VK_KHR_16BIT_STORAGE_EXTENSION_NAME;

  //=== VK_KHR_incremental_present ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRIncrementalPresentSpecVersion   = VK_KHR_INCREMENTAL_PRESENT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRIncrementalPresentExtensionName = VK_KHR_INCREMENTAL_PRESENT_EXTENSION_NAME;

  //=== VK_KHR_descriptor_update_template ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDescriptorUpdateTemplateSpecVersion   = VK_KHR_DESCRIPTOR_UPDATE_TEMPLATE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDescriptorUpdateTemplateExtensionName = VK_KHR_DESCRIPTOR_UPDATE_TEMPLATE_EXTENSION_NAME;

  //=== VK_NV_clip_space_w_scaling ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVClipSpaceWScalingSpecVersion   = VK_NV_CLIP_SPACE_W_SCALING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVClipSpaceWScalingExtensionName = VK_NV_CLIP_SPACE_W_SCALING_EXTENSION_NAME;

  //=== VK_EXT_direct_mode_display ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDirectModeDisplaySpecVersion   = VK_EXT_DIRECT_MODE_DISPLAY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDirectModeDisplayExtensionName = VK_EXT_DIRECT_MODE_DISPLAY_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_XLIB_XRANDR_EXT )
  //=== VK_EXT_acquire_xlib_display ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTAcquireXlibDisplaySpecVersion   = VK_EXT_ACQUIRE_XLIB_DISPLAY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTAcquireXlibDisplayExtensionName = VK_EXT_ACQUIRE_XLIB_DISPLAY_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_XLIB_XRANDR_EXT*/

  //=== VK_EXT_display_surface_counter ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDisplaySurfaceCounterSpecVersion   = VK_EXT_DISPLAY_SURFACE_COUNTER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDisplaySurfaceCounterExtensionName = VK_EXT_DISPLAY_SURFACE_COUNTER_EXTENSION_NAME;

  //=== VK_EXT_display_control ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDisplayControlSpecVersion   = VK_EXT_DISPLAY_CONTROL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDisplayControlExtensionName = VK_EXT_DISPLAY_CONTROL_EXTENSION_NAME;

  //=== VK_GOOGLE_display_timing ===
  VULKAN_HPP_CONSTEXPR_INLINE auto GOOGLEDisplayTimingSpecVersion   = VK_GOOGLE_DISPLAY_TIMING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto GOOGLEDisplayTimingExtensionName = VK_GOOGLE_DISPLAY_TIMING_EXTENSION_NAME;

  //=== VK_NV_sample_mask_override_coverage ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVSampleMaskOverrideCoverageSpecVersion   = VK_NV_SAMPLE_MASK_OVERRIDE_COVERAGE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVSampleMaskOverrideCoverageExtensionName = VK_NV_SAMPLE_MASK_OVERRIDE_COVERAGE_EXTENSION_NAME;

  //=== VK_NV_geometry_shader_passthrough ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVGeometryShaderPassthroughSpecVersion   = VK_NV_GEOMETRY_SHADER_PASSTHROUGH_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVGeometryShaderPassthroughExtensionName = VK_NV_GEOMETRY_SHADER_PASSTHROUGH_EXTENSION_NAME;

  //=== VK_NV_viewport_array2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVViewportArray2SpecVersion   = VK_NV_VIEWPORT_ARRAY_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVViewportArray2ExtensionName = VK_NV_VIEWPORT_ARRAY_2_EXTENSION_NAME;

  //=== VK_NVX_multiview_per_view_attributes ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVXMultiviewPerViewAttributesSpecVersion   = VK_NVX_MULTIVIEW_PER_VIEW_ATTRIBUTES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVXMultiviewPerViewAttributesExtensionName = VK_NVX_MULTIVIEW_PER_VIEW_ATTRIBUTES_EXTENSION_NAME;

  //=== VK_NV_viewport_swizzle ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVViewportSwizzleSpecVersion   = VK_NV_VIEWPORT_SWIZZLE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVViewportSwizzleExtensionName = VK_NV_VIEWPORT_SWIZZLE_EXTENSION_NAME;

  //=== VK_EXT_discard_rectangles ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDiscardRectanglesSpecVersion   = VK_EXT_DISCARD_RECTANGLES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDiscardRectanglesExtensionName = VK_EXT_DISCARD_RECTANGLES_EXTENSION_NAME;

  //=== VK_EXT_conservative_rasterization ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTConservativeRasterizationSpecVersion   = VK_EXT_CONSERVATIVE_RASTERIZATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTConservativeRasterizationExtensionName = VK_EXT_CONSERVATIVE_RASTERIZATION_EXTENSION_NAME;

  //=== VK_EXT_depth_clip_enable ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthClipEnableSpecVersion   = VK_EXT_DEPTH_CLIP_ENABLE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthClipEnableExtensionName = VK_EXT_DEPTH_CLIP_ENABLE_EXTENSION_NAME;

  //=== VK_EXT_swapchain_colorspace ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSwapchainColorSpaceSpecVersion   = VK_EXT_SWAPCHAIN_COLOR_SPACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSwapchainColorSpaceExtensionName = VK_EXT_SWAPCHAIN_COLOR_SPACE_EXTENSION_NAME;

  //=== VK_EXT_hdr_metadata ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTHdrMetadataSpecVersion   = VK_EXT_HDR_METADATA_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTHdrMetadataExtensionName = VK_EXT_HDR_METADATA_EXTENSION_NAME;

  //=== VK_KHR_imageless_framebuffer ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRImagelessFramebufferSpecVersion   = VK_KHR_IMAGELESS_FRAMEBUFFER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRImagelessFramebufferExtensionName = VK_KHR_IMAGELESS_FRAMEBUFFER_EXTENSION_NAME;

  //=== VK_KHR_create_renderpass2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRCreateRenderpass2SpecVersion   = VK_KHR_CREATE_RENDERPASS_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRCreateRenderpass2ExtensionName = VK_KHR_CREATE_RENDERPASS_2_EXTENSION_NAME;

  //=== VK_IMG_relaxed_line_rasterization ===
  VULKAN_HPP_CONSTEXPR_INLINE auto IMGRelaxedLineRasterizationSpecVersion   = VK_IMG_RELAXED_LINE_RASTERIZATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto IMGRelaxedLineRasterizationExtensionName = VK_IMG_RELAXED_LINE_RASTERIZATION_EXTENSION_NAME;

  //=== VK_KHR_shared_presentable_image ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSharedPresentableImageSpecVersion   = VK_KHR_SHARED_PRESENTABLE_IMAGE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSharedPresentableImageExtensionName = VK_KHR_SHARED_PRESENTABLE_IMAGE_EXTENSION_NAME;

  //=== VK_KHR_external_fence_capabilities ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalFenceCapabilitiesSpecVersion   = VK_KHR_EXTERNAL_FENCE_CAPABILITIES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalFenceCapabilitiesExtensionName = VK_KHR_EXTERNAL_FENCE_CAPABILITIES_EXTENSION_NAME;

  //=== VK_KHR_external_fence ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalFenceSpecVersion   = VK_KHR_EXTERNAL_FENCE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalFenceExtensionName = VK_KHR_EXTERNAL_FENCE_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_external_fence_win32 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalFenceWin32SpecVersion   = VK_KHR_EXTERNAL_FENCE_WIN32_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalFenceWin32ExtensionName = VK_KHR_EXTERNAL_FENCE_WIN32_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_external_fence_fd ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalFenceFdSpecVersion   = VK_KHR_EXTERNAL_FENCE_FD_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRExternalFenceFdExtensionName = VK_KHR_EXTERNAL_FENCE_FD_EXTENSION_NAME;

  //=== VK_KHR_performance_query ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPerformanceQuerySpecVersion   = VK_KHR_PERFORMANCE_QUERY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPerformanceQueryExtensionName = VK_KHR_PERFORMANCE_QUERY_EXTENSION_NAME;

  //=== VK_KHR_maintenance2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance2SpecVersion   = VK_KHR_MAINTENANCE_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance2ExtensionName = VK_KHR_MAINTENANCE_2_EXTENSION_NAME;

  //=== VK_KHR_get_surface_capabilities2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRGetSurfaceCapabilities2SpecVersion   = VK_KHR_GET_SURFACE_CAPABILITIES_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRGetSurfaceCapabilities2ExtensionName = VK_KHR_GET_SURFACE_CAPABILITIES_2_EXTENSION_NAME;

  //=== VK_KHR_variable_pointers ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVariablePointersSpecVersion   = VK_KHR_VARIABLE_POINTERS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVariablePointersExtensionName = VK_KHR_VARIABLE_POINTERS_EXTENSION_NAME;

  //=== VK_KHR_get_display_properties2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRGetDisplayProperties2SpecVersion   = VK_KHR_GET_DISPLAY_PROPERTIES_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRGetDisplayProperties2ExtensionName = VK_KHR_GET_DISPLAY_PROPERTIES_2_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_IOS_MVK )
  //=== VK_MVK_ios_surface ===
  VULKAN_HPP_DEPRECATED( "The VK_MVK_ios_surface extension has been deprecated by VK_EXT_metal_surface." )
  VULKAN_HPP_CONSTEXPR_INLINE auto MVKIosSurfaceSpecVersion = VK_MVK_IOS_SURFACE_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_MVK_ios_surface extension has been deprecated by VK_EXT_metal_surface." )
  VULKAN_HPP_CONSTEXPR_INLINE auto MVKIosSurfaceExtensionName = VK_MVK_IOS_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_IOS_MVK*/

#if defined( VK_USE_PLATFORM_MACOS_MVK )
  //=== VK_MVK_macos_surface ===
  VULKAN_HPP_DEPRECATED( "The VK_MVK_macos_surface extension has been deprecated by VK_EXT_metal_surface." )
  VULKAN_HPP_CONSTEXPR_INLINE auto MVKMacosSurfaceSpecVersion = VK_MVK_MACOS_SURFACE_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_MVK_macos_surface extension has been deprecated by VK_EXT_metal_surface." )
  VULKAN_HPP_CONSTEXPR_INLINE auto MVKMacosSurfaceExtensionName = VK_MVK_MACOS_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_MACOS_MVK*/

  //=== VK_EXT_external_memory_dma_buf ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExternalMemoryDmaBufSpecVersion   = VK_EXT_EXTERNAL_MEMORY_DMA_BUF_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExternalMemoryDmaBufExtensionName = VK_EXT_EXTERNAL_MEMORY_DMA_BUF_EXTENSION_NAME;

  //=== VK_EXT_queue_family_foreign ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTQueueFamilyForeignSpecVersion   = VK_EXT_QUEUE_FAMILY_FOREIGN_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTQueueFamilyForeignExtensionName = VK_EXT_QUEUE_FAMILY_FOREIGN_EXTENSION_NAME;

  //=== VK_KHR_dedicated_allocation ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDedicatedAllocationSpecVersion   = VK_KHR_DEDICATED_ALLOCATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDedicatedAllocationExtensionName = VK_KHR_DEDICATED_ALLOCATION_EXTENSION_NAME;

  //=== VK_EXT_debug_utils ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDebugUtilsSpecVersion   = VK_EXT_DEBUG_UTILS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDebugUtilsExtensionName = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_ANDROID_KHR )
  //=== VK_ANDROID_external_memory_android_hardware_buffer ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ANDROIDExternalMemoryAndroidHardwareBufferSpecVersion   = VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ANDROIDExternalMemoryAndroidHardwareBufferExtensionName = VK_ANDROID_EXTERNAL_MEMORY_ANDROID_HARDWARE_BUFFER_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_ANDROID_KHR*/

  //=== VK_EXT_sampler_filter_minmax ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSamplerFilterMinmaxSpecVersion   = VK_EXT_SAMPLER_FILTER_MINMAX_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSamplerFilterMinmaxExtensionName = VK_EXT_SAMPLER_FILTER_MINMAX_EXTENSION_NAME;

  //=== VK_KHR_storage_buffer_storage_class ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRStorageBufferStorageClassSpecVersion   = VK_KHR_STORAGE_BUFFER_STORAGE_CLASS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRStorageBufferStorageClassExtensionName = VK_KHR_STORAGE_BUFFER_STORAGE_CLASS_EXTENSION_NAME;

  //=== VK_AMD_gpu_shader_int16 ===
  VULKAN_HPP_DEPRECATED( "The VK_AMD_gpu_shader_int16 extension has been deprecated by VK_KHR_shader_float16_int8." )
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDGpuShaderInt16SpecVersion = VK_AMD_GPU_SHADER_INT16_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_AMD_gpu_shader_int16 extension has been deprecated by VK_KHR_shader_float16_int8." )
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDGpuShaderInt16ExtensionName = VK_AMD_GPU_SHADER_INT16_EXTENSION_NAME;

  //=== VK_AMD_gpa_interface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDGpaInterfaceSpecVersion   = VK_AMD_GPA_INTERFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDGpaInterfaceExtensionName = VK_AMD_GPA_INTERFACE_EXTENSION_NAME;

#if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_AMDX_shader_enqueue ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDXShaderEnqueueSpecVersion   = VK_AMDX_SHADER_ENQUEUE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDXShaderEnqueueExtensionName = VK_AMDX_SHADER_ENQUEUE_EXTENSION_NAME;
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_EXT_descriptor_heap ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDescriptorHeapSpecVersion   = VK_EXT_DESCRIPTOR_HEAP_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDescriptorHeapExtensionName = VK_EXT_DESCRIPTOR_HEAP_EXTENSION_NAME;

  //=== VK_AMD_mixed_attachment_samples ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDMixedAttachmentSamplesSpecVersion   = VK_AMD_MIXED_ATTACHMENT_SAMPLES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDMixedAttachmentSamplesExtensionName = VK_AMD_MIXED_ATTACHMENT_SAMPLES_EXTENSION_NAME;

  //=== VK_AMD_shader_fragment_mask ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderFragmentMaskSpecVersion   = VK_AMD_SHADER_FRAGMENT_MASK_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderFragmentMaskExtensionName = VK_AMD_SHADER_FRAGMENT_MASK_EXTENSION_NAME;

  //=== VK_EXT_inline_uniform_block ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTInlineUniformBlockSpecVersion   = VK_EXT_INLINE_UNIFORM_BLOCK_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTInlineUniformBlockExtensionName = VK_EXT_INLINE_UNIFORM_BLOCK_EXTENSION_NAME;

  //=== VK_EXT_shader_stencil_export ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderStencilExportSpecVersion   = VK_EXT_SHADER_STENCIL_EXPORT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderStencilExportExtensionName = VK_EXT_SHADER_STENCIL_EXPORT_EXTENSION_NAME;

  //=== VK_KHR_shader_bfloat16 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderBfloat16SpecVersion   = VK_KHR_SHADER_BFLOAT16_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderBfloat16ExtensionName = VK_KHR_SHADER_BFLOAT16_EXTENSION_NAME;

  //=== VK_EXT_sample_locations ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSampleLocationsSpecVersion   = VK_EXT_SAMPLE_LOCATIONS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSampleLocationsExtensionName = VK_EXT_SAMPLE_LOCATIONS_EXTENSION_NAME;

  //=== VK_KHR_relaxed_block_layout ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRelaxedBlockLayoutSpecVersion   = VK_KHR_RELAXED_BLOCK_LAYOUT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRelaxedBlockLayoutExtensionName = VK_KHR_RELAXED_BLOCK_LAYOUT_EXTENSION_NAME;

  //=== VK_KHR_get_memory_requirements2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRGetMemoryRequirements2SpecVersion   = VK_KHR_GET_MEMORY_REQUIREMENTS_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRGetMemoryRequirements2ExtensionName = VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME;

  //=== VK_KHR_image_format_list ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRImageFormatListSpecVersion   = VK_KHR_IMAGE_FORMAT_LIST_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRImageFormatListExtensionName = VK_KHR_IMAGE_FORMAT_LIST_EXTENSION_NAME;

  //=== VK_EXT_blend_operation_advanced ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTBlendOperationAdvancedSpecVersion   = VK_EXT_BLEND_OPERATION_ADVANCED_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTBlendOperationAdvancedExtensionName = VK_EXT_BLEND_OPERATION_ADVANCED_EXTENSION_NAME;

  //=== VK_NV_fragment_coverage_to_color ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVFragmentCoverageToColorSpecVersion   = VK_NV_FRAGMENT_COVERAGE_TO_COLOR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVFragmentCoverageToColorExtensionName = VK_NV_FRAGMENT_COVERAGE_TO_COLOR_EXTENSION_NAME;

  //=== VK_KHR_acceleration_structure ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRAccelerationStructureSpecVersion   = VK_KHR_ACCELERATION_STRUCTURE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRAccelerationStructureExtensionName = VK_KHR_ACCELERATION_STRUCTURE_EXTENSION_NAME;

  //=== VK_KHR_ray_tracing_pipeline ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRayTracingPipelineSpecVersion   = VK_KHR_RAY_TRACING_PIPELINE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRayTracingPipelineExtensionName = VK_KHR_RAY_TRACING_PIPELINE_EXTENSION_NAME;

  //=== VK_KHR_ray_query ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRayQuerySpecVersion   = VK_KHR_RAY_QUERY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRayQueryExtensionName = VK_KHR_RAY_QUERY_EXTENSION_NAME;

  //=== VK_NV_framebuffer_mixed_samples ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVFramebufferMixedSamplesSpecVersion   = VK_NV_FRAMEBUFFER_MIXED_SAMPLES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVFramebufferMixedSamplesExtensionName = VK_NV_FRAMEBUFFER_MIXED_SAMPLES_EXTENSION_NAME;

  //=== VK_NV_fill_rectangle ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVFillRectangleSpecVersion   = VK_NV_FILL_RECTANGLE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVFillRectangleExtensionName = VK_NV_FILL_RECTANGLE_EXTENSION_NAME;

  //=== VK_NV_shader_sm_builtins ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVShaderSmBuiltinsSpecVersion   = VK_NV_SHADER_SM_BUILTINS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVShaderSmBuiltinsExtensionName = VK_NV_SHADER_SM_BUILTINS_EXTENSION_NAME;

  //=== VK_EXT_post_depth_coverage ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPostDepthCoverageSpecVersion   = VK_EXT_POST_DEPTH_COVERAGE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPostDepthCoverageExtensionName = VK_EXT_POST_DEPTH_COVERAGE_EXTENSION_NAME;

  //=== VK_KHR_sampler_ycbcr_conversion ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSamplerYcbcrConversionSpecVersion   = VK_KHR_SAMPLER_YCBCR_CONVERSION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSamplerYcbcrConversionExtensionName = VK_KHR_SAMPLER_YCBCR_CONVERSION_EXTENSION_NAME;

  //=== VK_KHR_bind_memory2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRBindMemory2SpecVersion   = VK_KHR_BIND_MEMORY_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRBindMemory2ExtensionName = VK_KHR_BIND_MEMORY_2_EXTENSION_NAME;

  //=== VK_EXT_image_drm_format_modifier ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageDrmFormatModifierSpecVersion   = VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageDrmFormatModifierExtensionName = VK_EXT_IMAGE_DRM_FORMAT_MODIFIER_EXTENSION_NAME;

  //=== VK_EXT_validation_cache ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTValidationCacheSpecVersion   = VK_EXT_VALIDATION_CACHE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTValidationCacheExtensionName = VK_EXT_VALIDATION_CACHE_EXTENSION_NAME;

  //=== VK_EXT_descriptor_indexing ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDescriptorIndexingSpecVersion   = VK_EXT_DESCRIPTOR_INDEXING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDescriptorIndexingExtensionName = VK_EXT_DESCRIPTOR_INDEXING_EXTENSION_NAME;

  //=== VK_EXT_shader_viewport_index_layer ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderViewportIndexLayerSpecVersion   = VK_EXT_SHADER_VIEWPORT_INDEX_LAYER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderViewportIndexLayerExtensionName = VK_EXT_SHADER_VIEWPORT_INDEX_LAYER_EXTENSION_NAME;

#if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_KHR_portability_subset ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPortabilitySubsetSpecVersion   = VK_KHR_PORTABILITY_SUBSET_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPortabilitySubsetExtensionName = VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME;
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_NV_shading_rate_image ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVShadingRateImageSpecVersion   = VK_NV_SHADING_RATE_IMAGE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVShadingRateImageExtensionName = VK_NV_SHADING_RATE_IMAGE_EXTENSION_NAME;

  //=== VK_NV_ray_tracing ===
  VULKAN_HPP_DEPRECATED( "The VK_NV_ray_tracing extension has been deprecated by VK_KHR_ray_tracing_pipeline." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRayTracingSpecVersion = VK_NV_RAY_TRACING_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_NV_ray_tracing extension has been deprecated by VK_KHR_ray_tracing_pipeline." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRayTracingExtensionName = VK_NV_RAY_TRACING_EXTENSION_NAME;

  //=== VK_NV_representative_fragment_test ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRepresentativeFragmentTestSpecVersion   = VK_NV_REPRESENTATIVE_FRAGMENT_TEST_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRepresentativeFragmentTestExtensionName = VK_NV_REPRESENTATIVE_FRAGMENT_TEST_EXTENSION_NAME;

  //=== VK_KHR_maintenance3 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance3SpecVersion   = VK_KHR_MAINTENANCE_3_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance3ExtensionName = VK_KHR_MAINTENANCE_3_EXTENSION_NAME;

  //=== VK_KHR_draw_indirect_count ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDrawIndirectCountSpecVersion   = VK_KHR_DRAW_INDIRECT_COUNT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDrawIndirectCountExtensionName = VK_KHR_DRAW_INDIRECT_COUNT_EXTENSION_NAME;

  //=== VK_EXT_filter_cubic ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFilterCubicSpecVersion   = VK_EXT_FILTER_CUBIC_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFilterCubicExtensionName = VK_EXT_FILTER_CUBIC_EXTENSION_NAME;

  //=== VK_QCOM_render_pass_shader_resolve ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMRenderPassShaderResolveSpecVersion   = VK_QCOM_RENDER_PASS_SHADER_RESOLVE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMRenderPassShaderResolveExtensionName = VK_QCOM_RENDER_PASS_SHADER_RESOLVE_EXTENSION_NAME;

  //=== VK_QCOM_cooperative_matrix_conversion ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMCooperativeMatrixConversionSpecVersion   = VK_QCOM_COOPERATIVE_MATRIX_CONVERSION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMCooperativeMatrixConversionExtensionName = VK_QCOM_COOPERATIVE_MATRIX_CONVERSION_EXTENSION_NAME;

  //=== VK_QCOM_elapsed_timer_query ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMElapsedTimerQuerySpecVersion   = VK_QCOM_ELAPSED_TIMER_QUERY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMElapsedTimerQueryExtensionName = VK_QCOM_ELAPSED_TIMER_QUERY_EXTENSION_NAME;

  //=== VK_EXT_global_priority ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTGlobalPrioritySpecVersion   = VK_EXT_GLOBAL_PRIORITY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTGlobalPriorityExtensionName = VK_EXT_GLOBAL_PRIORITY_EXTENSION_NAME;

  //=== VK_KHR_shader_subgroup_extended_types ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderSubgroupExtendedTypesSpecVersion   = VK_KHR_SHADER_SUBGROUP_EXTENDED_TYPES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderSubgroupExtendedTypesExtensionName = VK_KHR_SHADER_SUBGROUP_EXTENDED_TYPES_EXTENSION_NAME;

  //=== VK_KHR_8bit_storage ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHR8BitStorageSpecVersion   = VK_KHR_8BIT_STORAGE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHR8BitStorageExtensionName = VK_KHR_8BIT_STORAGE_EXTENSION_NAME;

  //=== VK_EXT_external_memory_host ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExternalMemoryHostSpecVersion   = VK_EXT_EXTERNAL_MEMORY_HOST_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExternalMemoryHostExtensionName = VK_EXT_EXTERNAL_MEMORY_HOST_EXTENSION_NAME;

  //=== VK_AMD_buffer_marker ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDBufferMarkerSpecVersion   = VK_AMD_BUFFER_MARKER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDBufferMarkerExtensionName = VK_AMD_BUFFER_MARKER_EXTENSION_NAME;

  //=== VK_KHR_shader_atomic_int64 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderAtomicInt64SpecVersion   = VK_KHR_SHADER_ATOMIC_INT64_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderAtomicInt64ExtensionName = VK_KHR_SHADER_ATOMIC_INT64_EXTENSION_NAME;

  //=== VK_KHR_shader_clock ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderClockSpecVersion   = VK_KHR_SHADER_CLOCK_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderClockExtensionName = VK_KHR_SHADER_CLOCK_EXTENSION_NAME;

  //=== VK_AMD_pipeline_compiler_control ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDPipelineCompilerControlSpecVersion   = VK_AMD_PIPELINE_COMPILER_CONTROL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDPipelineCompilerControlExtensionName = VK_AMD_PIPELINE_COMPILER_CONTROL_EXTENSION_NAME;

  //=== VK_EXT_calibrated_timestamps ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTCalibratedTimestampsSpecVersion   = VK_EXT_CALIBRATED_TIMESTAMPS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTCalibratedTimestampsExtensionName = VK_EXT_CALIBRATED_TIMESTAMPS_EXTENSION_NAME;

  //=== VK_AMD_shader_core_properties ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderCorePropertiesSpecVersion   = VK_AMD_SHADER_CORE_PROPERTIES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderCorePropertiesExtensionName = VK_AMD_SHADER_CORE_PROPERTIES_EXTENSION_NAME;

  //=== VK_KHR_video_decode_h265 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoDecodeH265SpecVersion   = VK_KHR_VIDEO_DECODE_H265_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoDecodeH265ExtensionName = VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME;

  //=== VK_KHR_global_priority ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRGlobalPrioritySpecVersion   = VK_KHR_GLOBAL_PRIORITY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRGlobalPriorityExtensionName = VK_KHR_GLOBAL_PRIORITY_EXTENSION_NAME;

  //=== VK_AMD_memory_overallocation_behavior ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDMemoryOverallocationBehaviorSpecVersion   = VK_AMD_MEMORY_OVERALLOCATION_BEHAVIOR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDMemoryOverallocationBehaviorExtensionName = VK_AMD_MEMORY_OVERALLOCATION_BEHAVIOR_EXTENSION_NAME;

  //=== VK_EXT_vertex_attribute_divisor ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTVertexAttributeDivisorSpecVersion   = VK_EXT_VERTEX_ATTRIBUTE_DIVISOR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTVertexAttributeDivisorExtensionName = VK_EXT_VERTEX_ATTRIBUTE_DIVISOR_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_GGP )
  //=== VK_GGP_frame_token ===
  VULKAN_HPP_CONSTEXPR_INLINE auto GGPFrameTokenSpecVersion   = VK_GGP_FRAME_TOKEN_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto GGPFrameTokenExtensionName = VK_GGP_FRAME_TOKEN_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_GGP*/

  //=== VK_EXT_pipeline_creation_feedback ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelineCreationFeedbackSpecVersion   = VK_EXT_PIPELINE_CREATION_FEEDBACK_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelineCreationFeedbackExtensionName = VK_EXT_PIPELINE_CREATION_FEEDBACK_EXTENSION_NAME;

  //=== VK_KHR_driver_properties ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDriverPropertiesSpecVersion   = VK_KHR_DRIVER_PROPERTIES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDriverPropertiesExtensionName = VK_KHR_DRIVER_PROPERTIES_EXTENSION_NAME;

  //=== VK_KHR_shader_float_controls ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderFloatControlsSpecVersion   = VK_KHR_SHADER_FLOAT_CONTROLS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderFloatControlsExtensionName = VK_KHR_SHADER_FLOAT_CONTROLS_EXTENSION_NAME;

  //=== VK_NV_shader_subgroup_partitioned ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVShaderSubgroupPartitionedSpecVersion   = VK_NV_SHADER_SUBGROUP_PARTITIONED_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVShaderSubgroupPartitionedExtensionName = VK_NV_SHADER_SUBGROUP_PARTITIONED_EXTENSION_NAME;

  //=== VK_KHR_depth_stencil_resolve ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDepthStencilResolveSpecVersion   = VK_KHR_DEPTH_STENCIL_RESOLVE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDepthStencilResolveExtensionName = VK_KHR_DEPTH_STENCIL_RESOLVE_EXTENSION_NAME;

  //=== VK_KHR_swapchain_mutable_format ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSwapchainMutableFormatSpecVersion   = VK_KHR_SWAPCHAIN_MUTABLE_FORMAT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSwapchainMutableFormatExtensionName = VK_KHR_SWAPCHAIN_MUTABLE_FORMAT_EXTENSION_NAME;

  //=== VK_NV_compute_shader_derivatives ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVComputeShaderDerivativesSpecVersion   = VK_NV_COMPUTE_SHADER_DERIVATIVES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVComputeShaderDerivativesExtensionName = VK_NV_COMPUTE_SHADER_DERIVATIVES_EXTENSION_NAME;

  //=== VK_NV_mesh_shader ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVMeshShaderSpecVersion   = VK_NV_MESH_SHADER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVMeshShaderExtensionName = VK_NV_MESH_SHADER_EXTENSION_NAME;

  //=== VK_NV_fragment_shader_barycentric ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVFragmentShaderBarycentricSpecVersion   = VK_NV_FRAGMENT_SHADER_BARYCENTRIC_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVFragmentShaderBarycentricExtensionName = VK_NV_FRAGMENT_SHADER_BARYCENTRIC_EXTENSION_NAME;

  //=== VK_NV_shader_image_footprint ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVShaderImageFootprintSpecVersion   = VK_NV_SHADER_IMAGE_FOOTPRINT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVShaderImageFootprintExtensionName = VK_NV_SHADER_IMAGE_FOOTPRINT_EXTENSION_NAME;

  //=== VK_NV_scissor_exclusive ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVScissorExclusiveSpecVersion   = VK_NV_SCISSOR_EXCLUSIVE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVScissorExclusiveExtensionName = VK_NV_SCISSOR_EXCLUSIVE_EXTENSION_NAME;

  //=== VK_NV_device_diagnostic_checkpoints ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDeviceDiagnosticCheckpointsSpecVersion   = VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDeviceDiagnosticCheckpointsExtensionName = VK_NV_DEVICE_DIAGNOSTIC_CHECKPOINTS_EXTENSION_NAME;

  //=== VK_KHR_timeline_semaphore ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRTimelineSemaphoreSpecVersion   = VK_KHR_TIMELINE_SEMAPHORE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRTimelineSemaphoreExtensionName = VK_KHR_TIMELINE_SEMAPHORE_EXTENSION_NAME;

  //=== VK_EXT_present_timing ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPresentTimingSpecVersion   = VK_EXT_PRESENT_TIMING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPresentTimingExtensionName = VK_EXT_PRESENT_TIMING_EXTENSION_NAME;

  //=== VK_INTEL_shader_integer_functions2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto INTELShaderIntegerFunctions2SpecVersion   = VK_INTEL_SHADER_INTEGER_FUNCTIONS_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto INTELShaderIntegerFunctions2ExtensionName = VK_INTEL_SHADER_INTEGER_FUNCTIONS_2_EXTENSION_NAME;

  //=== VK_INTEL_performance_query ===
  VULKAN_HPP_CONSTEXPR_INLINE auto INTELPerformanceQuerySpecVersion   = VK_INTEL_PERFORMANCE_QUERY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto INTELPerformanceQueryExtensionName = VK_INTEL_PERFORMANCE_QUERY_EXTENSION_NAME;

  //=== VK_KHR_vulkan_memory_model ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVulkanMemoryModelSpecVersion   = VK_KHR_VULKAN_MEMORY_MODEL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVulkanMemoryModelExtensionName = VK_KHR_VULKAN_MEMORY_MODEL_EXTENSION_NAME;

  //=== VK_EXT_pci_bus_info ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPciBusInfoSpecVersion   = VK_EXT_PCI_BUS_INFO_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPciBusInfoExtensionName = VK_EXT_PCI_BUS_INFO_EXTENSION_NAME;

  //=== VK_AMD_display_native_hdr ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDDisplayNativeHdrSpecVersion   = VK_AMD_DISPLAY_NATIVE_HDR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDDisplayNativeHdrExtensionName = VK_AMD_DISPLAY_NATIVE_HDR_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_FUCHSIA )
  //=== VK_FUCHSIA_imagepipe_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto FUCHSIAImagepipeSurfaceSpecVersion   = VK_FUCHSIA_IMAGEPIPE_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto FUCHSIAImagepipeSurfaceExtensionName = VK_FUCHSIA_IMAGEPIPE_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_FUCHSIA*/

  //=== VK_KHR_shader_terminate_invocation ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderTerminateInvocationSpecVersion   = VK_KHR_SHADER_TERMINATE_INVOCATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderTerminateInvocationExtensionName = VK_KHR_SHADER_TERMINATE_INVOCATION_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_METAL_EXT )
  //=== VK_EXT_metal_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMetalSurfaceSpecVersion   = VK_EXT_METAL_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMetalSurfaceExtensionName = VK_EXT_METAL_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_METAL_EXT*/

  //=== VK_EXT_fragment_density_map ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFragmentDensityMapSpecVersion   = VK_EXT_FRAGMENT_DENSITY_MAP_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFragmentDensityMapExtensionName = VK_EXT_FRAGMENT_DENSITY_MAP_EXTENSION_NAME;

  //=== VK_EXT_scalar_block_layout ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTScalarBlockLayoutSpecVersion   = VK_EXT_SCALAR_BLOCK_LAYOUT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTScalarBlockLayoutExtensionName = VK_EXT_SCALAR_BLOCK_LAYOUT_EXTENSION_NAME;

  //=== VK_GOOGLE_hlsl_functionality1 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto GOOGLEHlslFunctionality1SpecVersion   = VK_GOOGLE_HLSL_FUNCTIONALITY_1_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto GOOGLEHlslFunctionality1ExtensionName = VK_GOOGLE_HLSL_FUNCTIONALITY_1_EXTENSION_NAME;

  //=== VK_GOOGLE_decorate_string ===
  VULKAN_HPP_CONSTEXPR_INLINE auto GOOGLEDecorateStringSpecVersion   = VK_GOOGLE_DECORATE_STRING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto GOOGLEDecorateStringExtensionName = VK_GOOGLE_DECORATE_STRING_EXTENSION_NAME;

  //=== VK_EXT_subgroup_size_control ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSubgroupSizeControlSpecVersion   = VK_EXT_SUBGROUP_SIZE_CONTROL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSubgroupSizeControlExtensionName = VK_EXT_SUBGROUP_SIZE_CONTROL_EXTENSION_NAME;

  //=== VK_KHR_fragment_shading_rate ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRFragmentShadingRateSpecVersion   = VK_KHR_FRAGMENT_SHADING_RATE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRFragmentShadingRateExtensionName = VK_KHR_FRAGMENT_SHADING_RATE_EXTENSION_NAME;

  //=== VK_AMD_shader_core_properties2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderCoreProperties2SpecVersion   = VK_AMD_SHADER_CORE_PROPERTIES_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderCoreProperties2ExtensionName = VK_AMD_SHADER_CORE_PROPERTIES_2_EXTENSION_NAME;

  //=== VK_AMD_device_coherent_memory ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDDeviceCoherentMemorySpecVersion   = VK_AMD_DEVICE_COHERENT_MEMORY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDDeviceCoherentMemoryExtensionName = VK_AMD_DEVICE_COHERENT_MEMORY_EXTENSION_NAME;

  //=== VK_KHR_shader_constant_data ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderConstantDataSpecVersion   = VK_KHR_SHADER_CONSTANT_DATA_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderConstantDataExtensionName = VK_KHR_SHADER_CONSTANT_DATA_EXTENSION_NAME;

  //=== VK_KHR_dynamic_rendering_local_read ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDynamicRenderingLocalReadSpecVersion   = VK_KHR_DYNAMIC_RENDERING_LOCAL_READ_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDynamicRenderingLocalReadExtensionName = VK_KHR_DYNAMIC_RENDERING_LOCAL_READ_EXTENSION_NAME;

  //=== VK_KHR_shader_abort ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderAbortSpecVersion   = VK_KHR_SHADER_ABORT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderAbortExtensionName = VK_KHR_SHADER_ABORT_EXTENSION_NAME;

  //=== VK_EXT_shader_image_atomic_int64 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderImageAtomicInt64SpecVersion   = VK_EXT_SHADER_IMAGE_ATOMIC_INT64_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderImageAtomicInt64ExtensionName = VK_EXT_SHADER_IMAGE_ATOMIC_INT64_EXTENSION_NAME;

  //=== VK_KHR_shader_quad_control ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderQuadControlSpecVersion   = VK_KHR_SHADER_QUAD_CONTROL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderQuadControlExtensionName = VK_KHR_SHADER_QUAD_CONTROL_EXTENSION_NAME;

  //=== VK_KHR_spirv_1_4 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSpirv14SpecVersion   = VK_KHR_SPIRV_1_4_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSpirv14ExtensionName = VK_KHR_SPIRV_1_4_EXTENSION_NAME;

  //=== VK_EXT_memory_budget ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMemoryBudgetSpecVersion   = VK_EXT_MEMORY_BUDGET_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMemoryBudgetExtensionName = VK_EXT_MEMORY_BUDGET_EXTENSION_NAME;

  //=== VK_EXT_memory_priority ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMemoryPrioritySpecVersion   = VK_EXT_MEMORY_PRIORITY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMemoryPriorityExtensionName = VK_EXT_MEMORY_PRIORITY_EXTENSION_NAME;

  //=== VK_KHR_surface_protected_capabilities ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSurfaceProtectedCapabilitiesSpecVersion   = VK_KHR_SURFACE_PROTECTED_CAPABILITIES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSurfaceProtectedCapabilitiesExtensionName = VK_KHR_SURFACE_PROTECTED_CAPABILITIES_EXTENSION_NAME;

  //=== VK_NV_dedicated_allocation_image_aliasing ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDedicatedAllocationImageAliasingSpecVersion   = VK_NV_DEDICATED_ALLOCATION_IMAGE_ALIASING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDedicatedAllocationImageAliasingExtensionName = VK_NV_DEDICATED_ALLOCATION_IMAGE_ALIASING_EXTENSION_NAME;

  //=== VK_KHR_separate_depth_stencil_layouts ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSeparateDepthStencilLayoutsSpecVersion   = VK_KHR_SEPARATE_DEPTH_STENCIL_LAYOUTS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSeparateDepthStencilLayoutsExtensionName = VK_KHR_SEPARATE_DEPTH_STENCIL_LAYOUTS_EXTENSION_NAME;

  //=== VK_EXT_buffer_device_address ===
  VULKAN_HPP_DEPRECATED( "The VK_EXT_buffer_device_address extension has been deprecated by VK_KHR_buffer_device_address." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTBufferDeviceAddressSpecVersion = VK_EXT_BUFFER_DEVICE_ADDRESS_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_EXT_buffer_device_address extension has been deprecated by VK_KHR_buffer_device_address." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTBufferDeviceAddressExtensionName = VK_EXT_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME;

  //=== VK_EXT_tooling_info ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTToolingInfoSpecVersion   = VK_EXT_TOOLING_INFO_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTToolingInfoExtensionName = VK_EXT_TOOLING_INFO_EXTENSION_NAME;

  //=== VK_EXT_separate_stencil_usage ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSeparateStencilUsageSpecVersion   = VK_EXT_SEPARATE_STENCIL_USAGE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSeparateStencilUsageExtensionName = VK_EXT_SEPARATE_STENCIL_USAGE_EXTENSION_NAME;

  //=== VK_EXT_validation_features ===
  VULKAN_HPP_DEPRECATED( "The VK_EXT_validation_features extension has been deprecated by VK_EXT_layer_settings." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTValidationFeaturesSpecVersion = VK_EXT_VALIDATION_FEATURES_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_EXT_validation_features extension has been deprecated by VK_EXT_layer_settings." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTValidationFeaturesExtensionName = VK_EXT_VALIDATION_FEATURES_EXTENSION_NAME;

  //=== VK_KHR_present_wait ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPresentWaitSpecVersion   = VK_KHR_PRESENT_WAIT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPresentWaitExtensionName = VK_KHR_PRESENT_WAIT_EXTENSION_NAME;

  //=== VK_NV_cooperative_matrix ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCooperativeMatrixSpecVersion   = VK_NV_COOPERATIVE_MATRIX_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCooperativeMatrixExtensionName = VK_NV_COOPERATIVE_MATRIX_EXTENSION_NAME;

  //=== VK_NV_coverage_reduction_mode ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCoverageReductionModeSpecVersion   = VK_NV_COVERAGE_REDUCTION_MODE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCoverageReductionModeExtensionName = VK_NV_COVERAGE_REDUCTION_MODE_EXTENSION_NAME;

  //=== VK_EXT_fragment_shader_interlock ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFragmentShaderInterlockSpecVersion   = VK_EXT_FRAGMENT_SHADER_INTERLOCK_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFragmentShaderInterlockExtensionName = VK_EXT_FRAGMENT_SHADER_INTERLOCK_EXTENSION_NAME;

  //=== VK_EXT_ycbcr_image_arrays ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTYcbcrImageArraysSpecVersion   = VK_EXT_YCBCR_IMAGE_ARRAYS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTYcbcrImageArraysExtensionName = VK_EXT_YCBCR_IMAGE_ARRAYS_EXTENSION_NAME;

  //=== VK_KHR_uniform_buffer_standard_layout ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRUniformBufferStandardLayoutSpecVersion   = VK_KHR_UNIFORM_BUFFER_STANDARD_LAYOUT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRUniformBufferStandardLayoutExtensionName = VK_KHR_UNIFORM_BUFFER_STANDARD_LAYOUT_EXTENSION_NAME;

  //=== VK_EXT_provoking_vertex ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTProvokingVertexSpecVersion   = VK_EXT_PROVOKING_VERTEX_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTProvokingVertexExtensionName = VK_EXT_PROVOKING_VERTEX_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_EXT_full_screen_exclusive ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFullScreenExclusiveSpecVersion   = VK_EXT_FULL_SCREEN_EXCLUSIVE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFullScreenExclusiveExtensionName = VK_EXT_FULL_SCREEN_EXCLUSIVE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_EXT_headless_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTHeadlessSurfaceSpecVersion   = VK_EXT_HEADLESS_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTHeadlessSurfaceExtensionName = VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME;

  //=== VK_KHR_buffer_device_address ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRBufferDeviceAddressSpecVersion   = VK_KHR_BUFFER_DEVICE_ADDRESS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRBufferDeviceAddressExtensionName = VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME;

  //=== VK_EXT_line_rasterization ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTLineRasterizationSpecVersion   = VK_EXT_LINE_RASTERIZATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTLineRasterizationExtensionName = VK_EXT_LINE_RASTERIZATION_EXTENSION_NAME;

  //=== VK_EXT_shader_atomic_float ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderAtomicFloatSpecVersion   = VK_EXT_SHADER_ATOMIC_FLOAT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderAtomicFloatExtensionName = VK_EXT_SHADER_ATOMIC_FLOAT_EXTENSION_NAME;

  //=== VK_EXT_host_query_reset ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTHostQueryResetSpecVersion   = VK_EXT_HOST_QUERY_RESET_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTHostQueryResetExtensionName = VK_EXT_HOST_QUERY_RESET_EXTENSION_NAME;

  //=== VK_EXT_index_type_uint8 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTIndexTypeUint8SpecVersion   = VK_EXT_INDEX_TYPE_UINT8_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTIndexTypeUint8ExtensionName = VK_EXT_INDEX_TYPE_UINT8_EXTENSION_NAME;

  //=== VK_EXT_extended_dynamic_state ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExtendedDynamicStateSpecVersion   = VK_EXT_EXTENDED_DYNAMIC_STATE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExtendedDynamicStateExtensionName = VK_EXT_EXTENDED_DYNAMIC_STATE_EXTENSION_NAME;

  //=== VK_KHR_deferred_host_operations ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDeferredHostOperationsSpecVersion   = VK_KHR_DEFERRED_HOST_OPERATIONS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDeferredHostOperationsExtensionName = VK_KHR_DEFERRED_HOST_OPERATIONS_EXTENSION_NAME;

  //=== VK_KHR_pipeline_executable_properties ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPipelineExecutablePropertiesSpecVersion   = VK_KHR_PIPELINE_EXECUTABLE_PROPERTIES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPipelineExecutablePropertiesExtensionName = VK_KHR_PIPELINE_EXECUTABLE_PROPERTIES_EXTENSION_NAME;

  //=== VK_EXT_host_image_copy ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTHostImageCopySpecVersion   = VK_EXT_HOST_IMAGE_COPY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTHostImageCopyExtensionName = VK_EXT_HOST_IMAGE_COPY_EXTENSION_NAME;

  //=== VK_KHR_map_memory2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMapMemory2SpecVersion   = VK_KHR_MAP_MEMORY_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMapMemory2ExtensionName = VK_KHR_MAP_MEMORY_2_EXTENSION_NAME;

  //=== VK_EXT_map_memory_placed ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMapMemoryPlacedSpecVersion   = VK_EXT_MAP_MEMORY_PLACED_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMapMemoryPlacedExtensionName = VK_EXT_MAP_MEMORY_PLACED_EXTENSION_NAME;

  //=== VK_EXT_shader_atomic_float2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderAtomicFloat2SpecVersion   = VK_EXT_SHADER_ATOMIC_FLOAT_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderAtomicFloat2ExtensionName = VK_EXT_SHADER_ATOMIC_FLOAT_2_EXTENSION_NAME;

  //=== VK_EXT_surface_maintenance1 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSurfaceMaintenance1SpecVersion   = VK_EXT_SURFACE_MAINTENANCE_1_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSurfaceMaintenance1ExtensionName = VK_EXT_SURFACE_MAINTENANCE_1_EXTENSION_NAME;

  //=== VK_EXT_swapchain_maintenance1 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSwapchainMaintenance1SpecVersion   = VK_EXT_SWAPCHAIN_MAINTENANCE_1_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSwapchainMaintenance1ExtensionName = VK_EXT_SWAPCHAIN_MAINTENANCE_1_EXTENSION_NAME;

  //=== VK_EXT_shader_demote_to_helper_invocation ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderDemoteToHelperInvocationSpecVersion   = VK_EXT_SHADER_DEMOTE_TO_HELPER_INVOCATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderDemoteToHelperInvocationExtensionName = VK_EXT_SHADER_DEMOTE_TO_HELPER_INVOCATION_EXTENSION_NAME;

  //=== VK_NV_device_generated_commands ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDeviceGeneratedCommandsSpecVersion   = VK_NV_DEVICE_GENERATED_COMMANDS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDeviceGeneratedCommandsExtensionName = VK_NV_DEVICE_GENERATED_COMMANDS_EXTENSION_NAME;

  //=== VK_NV_inherited_viewport_scissor ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVInheritedViewportScissorSpecVersion   = VK_NV_INHERITED_VIEWPORT_SCISSOR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVInheritedViewportScissorExtensionName = VK_NV_INHERITED_VIEWPORT_SCISSOR_EXTENSION_NAME;

  //=== VK_KHR_shader_integer_dot_product ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderIntegerDotProductSpecVersion   = VK_KHR_SHADER_INTEGER_DOT_PRODUCT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderIntegerDotProductExtensionName = VK_KHR_SHADER_INTEGER_DOT_PRODUCT_EXTENSION_NAME;

  //=== VK_EXT_texel_buffer_alignment ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTTexelBufferAlignmentSpecVersion   = VK_EXT_TEXEL_BUFFER_ALIGNMENT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTTexelBufferAlignmentExtensionName = VK_EXT_TEXEL_BUFFER_ALIGNMENT_EXTENSION_NAME;

  //=== VK_QCOM_render_pass_transform ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMRenderPassTransformSpecVersion   = VK_QCOM_RENDER_PASS_TRANSFORM_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMRenderPassTransformExtensionName = VK_QCOM_RENDER_PASS_TRANSFORM_EXTENSION_NAME;

  //=== VK_EXT_depth_bias_control ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthBiasControlSpecVersion   = VK_EXT_DEPTH_BIAS_CONTROL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthBiasControlExtensionName = VK_EXT_DEPTH_BIAS_CONTROL_EXTENSION_NAME;

  //=== VK_EXT_device_memory_report ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDeviceMemoryReportSpecVersion   = VK_EXT_DEVICE_MEMORY_REPORT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDeviceMemoryReportExtensionName = VK_EXT_DEVICE_MEMORY_REPORT_EXTENSION_NAME;

  //=== VK_EXT_acquire_drm_display ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTAcquireDrmDisplaySpecVersion   = VK_EXT_ACQUIRE_DRM_DISPLAY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTAcquireDrmDisplayExtensionName = VK_EXT_ACQUIRE_DRM_DISPLAY_EXTENSION_NAME;

  //=== VK_EXT_robustness2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTRobustness2SpecVersion   = VK_EXT_ROBUSTNESS_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTRobustness2ExtensionName = VK_EXT_ROBUSTNESS_2_EXTENSION_NAME;

  //=== VK_EXT_custom_border_color ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTCustomBorderColorSpecVersion   = VK_EXT_CUSTOM_BORDER_COLOR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTCustomBorderColorExtensionName = VK_EXT_CUSTOM_BORDER_COLOR_EXTENSION_NAME;

  //=== VK_EXT_texture_compression_astc_3d ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTTextureCompressionAstc3DSpecVersion   = VK_EXT_TEXTURE_COMPRESSION_ASTC_3D_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTTextureCompressionAstc3DExtensionName = VK_EXT_TEXTURE_COMPRESSION_ASTC_3D_EXTENSION_NAME;

  //=== VK_GOOGLE_user_type ===
  VULKAN_HPP_CONSTEXPR_INLINE auto GOOGLEUserTypeSpecVersion   = VK_GOOGLE_USER_TYPE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto GOOGLEUserTypeExtensionName = VK_GOOGLE_USER_TYPE_EXTENSION_NAME;

  //=== VK_KHR_pipeline_library ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPipelineLibrarySpecVersion   = VK_KHR_PIPELINE_LIBRARY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPipelineLibraryExtensionName = VK_KHR_PIPELINE_LIBRARY_EXTENSION_NAME;

  //=== VK_NV_present_barrier ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVPresentBarrierSpecVersion   = VK_NV_PRESENT_BARRIER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVPresentBarrierExtensionName = VK_NV_PRESENT_BARRIER_EXTENSION_NAME;

  //=== VK_KHR_shader_non_semantic_info ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderNonSemanticInfoSpecVersion   = VK_KHR_SHADER_NON_SEMANTIC_INFO_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderNonSemanticInfoExtensionName = VK_KHR_SHADER_NON_SEMANTIC_INFO_EXTENSION_NAME;

  //=== VK_KHR_present_id ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPresentIdSpecVersion   = VK_KHR_PRESENT_ID_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPresentIdExtensionName = VK_KHR_PRESENT_ID_EXTENSION_NAME;

  //=== VK_EXT_private_data ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPrivateDataSpecVersion   = VK_EXT_PRIVATE_DATA_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPrivateDataExtensionName = VK_EXT_PRIVATE_DATA_EXTENSION_NAME;

  //=== VK_EXT_pipeline_creation_cache_control ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelineCreationCacheControlSpecVersion   = VK_EXT_PIPELINE_CREATION_CACHE_CONTROL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelineCreationCacheControlExtensionName = VK_EXT_PIPELINE_CREATION_CACHE_CONTROL_EXTENSION_NAME;

  //=== VK_KHR_video_encode_queue ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeQueueSpecVersion   = VK_KHR_VIDEO_ENCODE_QUEUE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeQueueExtensionName = VK_KHR_VIDEO_ENCODE_QUEUE_EXTENSION_NAME;

  //=== VK_NV_device_diagnostics_config ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDeviceDiagnosticsConfigSpecVersion   = VK_NV_DEVICE_DIAGNOSTICS_CONFIG_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDeviceDiagnosticsConfigExtensionName = VK_NV_DEVICE_DIAGNOSTICS_CONFIG_EXTENSION_NAME;

  //=== VK_QCOM_render_pass_store_ops ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMRenderPassStoreOpsSpecVersion   = VK_QCOM_RENDER_PASS_STORE_OPS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMRenderPassStoreOpsExtensionName = VK_QCOM_RENDER_PASS_STORE_OPS_EXTENSION_NAME;

  //=== VK_QCOM_queue_perf_hint ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMQueuePerfHintSpecVersion   = VK_QCOM_QUEUE_PERF_HINT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMQueuePerfHintExtensionName = VK_QCOM_QUEUE_PERF_HINT_EXTENSION_NAME;

  //=== VK_QCOM_image_processing3 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMImageProcessing3SpecVersion   = VK_QCOM_IMAGE_PROCESSING_3_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMImageProcessing3ExtensionName = VK_QCOM_IMAGE_PROCESSING_3_EXTENSION_NAME;

  //=== VK_QCOM_shader_multiple_wait_queues ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMShaderMultipleWaitQueuesSpecVersion   = VK_QCOM_SHADER_MULTIPLE_WAIT_QUEUES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMShaderMultipleWaitQueuesExtensionName = VK_QCOM_SHADER_MULTIPLE_WAIT_QUEUES_EXTENSION_NAME;

  //=== VK_EXT_shader_split_barrier ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderSplitBarrierSpecVersion   = VK_EXT_SHADER_SPLIT_BARRIER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderSplitBarrierExtensionName = VK_EXT_SHADER_SPLIT_BARRIER_EXTENSION_NAME;

#if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_NV_cuda_kernel_launch ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCudaKernelLaunchSpecVersion   = VK_NV_CUDA_KERNEL_LAUNCH_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCudaKernelLaunchExtensionName = VK_NV_CUDA_KERNEL_LAUNCH_EXTENSION_NAME;
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_QCOM_tile_shading ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMTileShadingSpecVersion   = VK_QCOM_TILE_SHADING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMTileShadingExtensionName = VK_QCOM_TILE_SHADING_EXTENSION_NAME;

  //=== VK_NV_low_latency ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVLowLatencySpecVersion   = VK_NV_LOW_LATENCY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVLowLatencyExtensionName = VK_NV_LOW_LATENCY_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_METAL_EXT )
  //=== VK_EXT_metal_objects ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMetalObjectsSpecVersion   = VK_EXT_METAL_OBJECTS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMetalObjectsExtensionName = VK_EXT_METAL_OBJECTS_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_METAL_EXT*/

  //=== VK_KHR_synchronization2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSynchronization2SpecVersion   = VK_KHR_SYNCHRONIZATION_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSynchronization2ExtensionName = VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME;

  //=== VK_EXT_descriptor_buffer ===
  VULKAN_HPP_DEPRECATED( "The VK_EXT_descriptor_buffer extension has been deprecated by VK_EXT_descriptor_heap." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDescriptorBufferSpecVersion = VK_EXT_DESCRIPTOR_BUFFER_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_EXT_descriptor_buffer extension has been deprecated by VK_EXT_descriptor_heap." )
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDescriptorBufferExtensionName = VK_EXT_DESCRIPTOR_BUFFER_EXTENSION_NAME;

  //=== VK_KHR_device_address_commands ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDeviceAddressCommandsSpecVersion   = VK_KHR_DEVICE_ADDRESS_COMMANDS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDeviceAddressCommandsExtensionName = VK_KHR_DEVICE_ADDRESS_COMMANDS_EXTENSION_NAME;

  //=== VK_EXT_graphics_pipeline_library ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTGraphicsPipelineLibrarySpecVersion   = VK_EXT_GRAPHICS_PIPELINE_LIBRARY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTGraphicsPipelineLibraryExtensionName = VK_EXT_GRAPHICS_PIPELINE_LIBRARY_EXTENSION_NAME;

  //=== VK_AMD_shader_early_and_late_fragment_tests ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderEarlyAndLateFragmentTestsSpecVersion   = VK_AMD_SHADER_EARLY_AND_LATE_FRAGMENT_TESTS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDShaderEarlyAndLateFragmentTestsExtensionName = VK_AMD_SHADER_EARLY_AND_LATE_FRAGMENT_TESTS_EXTENSION_NAME;

  //=== VK_KHR_fragment_shader_barycentric ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRFragmentShaderBarycentricSpecVersion   = VK_KHR_FRAGMENT_SHADER_BARYCENTRIC_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRFragmentShaderBarycentricExtensionName = VK_KHR_FRAGMENT_SHADER_BARYCENTRIC_EXTENSION_NAME;

  //=== VK_KHR_shader_subgroup_uniform_control_flow ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderSubgroupUniformControlFlowSpecVersion   = VK_KHR_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderSubgroupUniformControlFlowExtensionName = VK_KHR_SHADER_SUBGROUP_UNIFORM_CONTROL_FLOW_EXTENSION_NAME;

  //=== VK_KHR_zero_initialize_workgroup_memory ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRZeroInitializeWorkgroupMemorySpecVersion   = VK_KHR_ZERO_INITIALIZE_WORKGROUP_MEMORY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRZeroInitializeWorkgroupMemoryExtensionName = VK_KHR_ZERO_INITIALIZE_WORKGROUP_MEMORY_EXTENSION_NAME;

  //=== VK_NV_fragment_shading_rate_enums ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVFragmentShadingRateEnumsSpecVersion   = VK_NV_FRAGMENT_SHADING_RATE_ENUMS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVFragmentShadingRateEnumsExtensionName = VK_NV_FRAGMENT_SHADING_RATE_ENUMS_EXTENSION_NAME;

  //=== VK_NV_ray_tracing_motion_blur ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRayTracingMotionBlurSpecVersion   = VK_NV_RAY_TRACING_MOTION_BLUR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRayTracingMotionBlurExtensionName = VK_NV_RAY_TRACING_MOTION_BLUR_EXTENSION_NAME;

  //=== VK_EXT_mesh_shader ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMeshShaderSpecVersion   = VK_EXT_MESH_SHADER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMeshShaderExtensionName = VK_EXT_MESH_SHADER_EXTENSION_NAME;

  //=== VK_EXT_ycbcr_2plane_444_formats ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTYcbcr2Plane444FormatsSpecVersion   = VK_EXT_YCBCR_2PLANE_444_FORMATS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTYcbcr2Plane444FormatsExtensionName = VK_EXT_YCBCR_2PLANE_444_FORMATS_EXTENSION_NAME;

  //=== VK_EXT_fragment_density_map2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFragmentDensityMap2SpecVersion   = VK_EXT_FRAGMENT_DENSITY_MAP_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFragmentDensityMap2ExtensionName = VK_EXT_FRAGMENT_DENSITY_MAP_2_EXTENSION_NAME;

  //=== VK_QCOM_rotated_copy_commands ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMRotatedCopyCommandsSpecVersion   = VK_QCOM_ROTATED_COPY_COMMANDS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMRotatedCopyCommandsExtensionName = VK_QCOM_ROTATED_COPY_COMMANDS_EXTENSION_NAME;

  //=== VK_EXT_image_robustness ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageRobustnessSpecVersion   = VK_EXT_IMAGE_ROBUSTNESS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageRobustnessExtensionName = VK_EXT_IMAGE_ROBUSTNESS_EXTENSION_NAME;

  //=== VK_KHR_workgroup_memory_explicit_layout ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRWorkgroupMemoryExplicitLayoutSpecVersion   = VK_KHR_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRWorkgroupMemoryExplicitLayoutExtensionName = VK_KHR_WORKGROUP_MEMORY_EXPLICIT_LAYOUT_EXTENSION_NAME;

  //=== VK_KHR_copy_commands2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRCopyCommands2SpecVersion   = VK_KHR_COPY_COMMANDS_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRCopyCommands2ExtensionName = VK_KHR_COPY_COMMANDS_2_EXTENSION_NAME;

  //=== VK_EXT_image_compression_control ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageCompressionControlSpecVersion   = VK_EXT_IMAGE_COMPRESSION_CONTROL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageCompressionControlExtensionName = VK_EXT_IMAGE_COMPRESSION_CONTROL_EXTENSION_NAME;

  //=== VK_EXT_attachment_feedback_loop_layout ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTAttachmentFeedbackLoopLayoutSpecVersion   = VK_EXT_ATTACHMENT_FEEDBACK_LOOP_LAYOUT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTAttachmentFeedbackLoopLayoutExtensionName = VK_EXT_ATTACHMENT_FEEDBACK_LOOP_LAYOUT_EXTENSION_NAME;

  //=== VK_EXT_4444_formats ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXT4444FormatsSpecVersion   = VK_EXT_4444_FORMATS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXT4444FormatsExtensionName = VK_EXT_4444_FORMATS_EXTENSION_NAME;

  //=== VK_EXT_device_fault ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDeviceFaultSpecVersion   = VK_EXT_DEVICE_FAULT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDeviceFaultExtensionName = VK_EXT_DEVICE_FAULT_EXTENSION_NAME;

  //=== VK_ARM_rasterization_order_attachment_access ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMRasterizationOrderAttachmentAccessSpecVersion   = VK_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMRasterizationOrderAttachmentAccessExtensionName = VK_ARM_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_EXTENSION_NAME;

  //=== VK_EXT_rgba10x6_formats ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTRgba10X6FormatsSpecVersion   = VK_EXT_RGBA10X6_FORMATS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTRgba10X6FormatsExtensionName = VK_EXT_RGBA10X6_FORMATS_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_NV_acquire_winrt_display ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVAcquireWinrtDisplaySpecVersion   = VK_NV_ACQUIRE_WINRT_DISPLAY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVAcquireWinrtDisplayExtensionName = VK_NV_ACQUIRE_WINRT_DISPLAY_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

#if defined( VK_USE_PLATFORM_DIRECTFB_EXT )
  //=== VK_EXT_directfb_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDirectfbSurfaceSpecVersion   = VK_EXT_DIRECTFB_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDirectfbSurfaceExtensionName = VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_DIRECTFB_EXT*/

  //=== VK_VALVE_mutable_descriptor_type ===
  VULKAN_HPP_CONSTEXPR_INLINE auto VALVEMutableDescriptorTypeSpecVersion   = VK_VALVE_MUTABLE_DESCRIPTOR_TYPE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto VALVEMutableDescriptorTypeExtensionName = VK_VALVE_MUTABLE_DESCRIPTOR_TYPE_EXTENSION_NAME;

  //=== VK_EXT_vertex_input_dynamic_state ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTVertexInputDynamicStateSpecVersion   = VK_EXT_VERTEX_INPUT_DYNAMIC_STATE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTVertexInputDynamicStateExtensionName = VK_EXT_VERTEX_INPUT_DYNAMIC_STATE_EXTENSION_NAME;

  //=== VK_EXT_physical_device_drm ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPhysicalDeviceDrmSpecVersion   = VK_EXT_PHYSICAL_DEVICE_DRM_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPhysicalDeviceDrmExtensionName = VK_EXT_PHYSICAL_DEVICE_DRM_EXTENSION_NAME;

  //=== VK_EXT_device_address_binding_report ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDeviceAddressBindingReportSpecVersion   = VK_EXT_DEVICE_ADDRESS_BINDING_REPORT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDeviceAddressBindingReportExtensionName = VK_EXT_DEVICE_ADDRESS_BINDING_REPORT_EXTENSION_NAME;

  //=== VK_EXT_depth_clip_control ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthClipControlSpecVersion   = VK_EXT_DEPTH_CLIP_CONTROL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthClipControlExtensionName = VK_EXT_DEPTH_CLIP_CONTROL_EXTENSION_NAME;

  //=== VK_EXT_primitive_topology_list_restart ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPrimitiveTopologyListRestartSpecVersion   = VK_EXT_PRIMITIVE_TOPOLOGY_LIST_RESTART_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPrimitiveTopologyListRestartExtensionName = VK_EXT_PRIMITIVE_TOPOLOGY_LIST_RESTART_EXTENSION_NAME;

  //=== VK_KHR_format_feature_flags2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRFormatFeatureFlags2SpecVersion   = VK_KHR_FORMAT_FEATURE_FLAGS_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRFormatFeatureFlags2ExtensionName = VK_KHR_FORMAT_FEATURE_FLAGS_2_EXTENSION_NAME;

  //=== VK_EXT_present_mode_fifo_latest_ready ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPresentModeFifoLatestReadySpecVersion   = VK_EXT_PRESENT_MODE_FIFO_LATEST_READY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPresentModeFifoLatestReadyExtensionName = VK_EXT_PRESENT_MODE_FIFO_LATEST_READY_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_FUCHSIA )
  //=== VK_FUCHSIA_external_memory ===
  VULKAN_HPP_CONSTEXPR_INLINE auto FUCHSIAExternalMemorySpecVersion   = VK_FUCHSIA_EXTERNAL_MEMORY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto FUCHSIAExternalMemoryExtensionName = VK_FUCHSIA_EXTERNAL_MEMORY_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
  //=== VK_FUCHSIA_external_semaphore ===
  VULKAN_HPP_CONSTEXPR_INLINE auto FUCHSIAExternalSemaphoreSpecVersion   = VK_FUCHSIA_EXTERNAL_SEMAPHORE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto FUCHSIAExternalSemaphoreExtensionName = VK_FUCHSIA_EXTERNAL_SEMAPHORE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
  //=== VK_FUCHSIA_buffer_collection ===
  VULKAN_HPP_CONSTEXPR_INLINE auto FUCHSIABufferCollectionSpecVersion   = VK_FUCHSIA_BUFFER_COLLECTION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto FUCHSIABufferCollectionExtensionName = VK_FUCHSIA_BUFFER_COLLECTION_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_FUCHSIA*/

  //=== VK_HUAWEI_subpass_shading ===
  VULKAN_HPP_CONSTEXPR_INLINE auto HUAWEISubpassShadingSpecVersion   = VK_HUAWEI_SUBPASS_SHADING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto HUAWEISubpassShadingExtensionName = VK_HUAWEI_SUBPASS_SHADING_EXTENSION_NAME;

  //=== VK_HUAWEI_invocation_mask ===
  VULKAN_HPP_CONSTEXPR_INLINE auto HUAWEIInvocationMaskSpecVersion   = VK_HUAWEI_INVOCATION_MASK_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto HUAWEIInvocationMaskExtensionName = VK_HUAWEI_INVOCATION_MASK_EXTENSION_NAME;

  //=== VK_NV_external_memory_rdma ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExternalMemoryRdmaSpecVersion   = VK_NV_EXTERNAL_MEMORY_RDMA_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExternalMemoryRdmaExtensionName = VK_NV_EXTERNAL_MEMORY_RDMA_EXTENSION_NAME;

  //=== VK_EXT_pipeline_properties ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelinePropertiesSpecVersion   = VK_EXT_PIPELINE_PROPERTIES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelinePropertiesExtensionName = VK_EXT_PIPELINE_PROPERTIES_EXTENSION_NAME;

  //=== VK_EXT_frame_boundary ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFrameBoundarySpecVersion   = VK_EXT_FRAME_BOUNDARY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFrameBoundaryExtensionName = VK_EXT_FRAME_BOUNDARY_EXTENSION_NAME;

  //=== VK_EXT_multisampled_render_to_single_sampled ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMultisampledRenderToSingleSampledSpecVersion   = VK_EXT_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMultisampledRenderToSingleSampledExtensionName = VK_EXT_MULTISAMPLED_RENDER_TO_SINGLE_SAMPLED_EXTENSION_NAME;

  //=== VK_EXT_extended_dynamic_state2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExtendedDynamicState2SpecVersion   = VK_EXT_EXTENDED_DYNAMIC_STATE_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExtendedDynamicState2ExtensionName = VK_EXT_EXTENDED_DYNAMIC_STATE_2_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_SCREEN_QNX )
  //=== VK_QNX_screen_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QNXScreenSurfaceSpecVersion   = VK_QNX_SCREEN_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QNXScreenSurfaceExtensionName = VK_QNX_SCREEN_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_SCREEN_QNX*/

  //=== VK_EXT_color_write_enable ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTColorWriteEnableSpecVersion   = VK_EXT_COLOR_WRITE_ENABLE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTColorWriteEnableExtensionName = VK_EXT_COLOR_WRITE_ENABLE_EXTENSION_NAME;

  //=== VK_EXT_primitives_generated_query ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPrimitivesGeneratedQuerySpecVersion   = VK_EXT_PRIMITIVES_GENERATED_QUERY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPrimitivesGeneratedQueryExtensionName = VK_EXT_PRIMITIVES_GENERATED_QUERY_EXTENSION_NAME;

  //=== VK_KHR_ray_tracing_maintenance1 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRayTracingMaintenance1SpecVersion   = VK_KHR_RAY_TRACING_MAINTENANCE_1_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRayTracingMaintenance1ExtensionName = VK_KHR_RAY_TRACING_MAINTENANCE_1_EXTENSION_NAME;

  //=== VK_KHR_shader_untyped_pointers ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderUntypedPointersSpecVersion   = VK_KHR_SHADER_UNTYPED_POINTERS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderUntypedPointersExtensionName = VK_KHR_SHADER_UNTYPED_POINTERS_EXTENSION_NAME;

  //=== VK_EXT_global_priority_query ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTGlobalPriorityQuerySpecVersion   = VK_EXT_GLOBAL_PRIORITY_QUERY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTGlobalPriorityQueryExtensionName = VK_EXT_GLOBAL_PRIORITY_QUERY_EXTENSION_NAME;

  //=== VK_VALVE_video_encode_rgb_conversion ===
  VULKAN_HPP_CONSTEXPR_INLINE auto VALVEVideoEncodeRgbConversionSpecVersion   = VK_VALVE_VIDEO_ENCODE_RGB_CONVERSION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto VALVEVideoEncodeRgbConversionExtensionName = VK_VALVE_VIDEO_ENCODE_RGB_CONVERSION_EXTENSION_NAME;

  //=== VK_EXT_image_view_min_lod ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageViewMinLodSpecVersion   = VK_EXT_IMAGE_VIEW_MIN_LOD_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageViewMinLodExtensionName = VK_EXT_IMAGE_VIEW_MIN_LOD_EXTENSION_NAME;

  //=== VK_EXT_multi_draw ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMultiDrawSpecVersion   = VK_EXT_MULTI_DRAW_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMultiDrawExtensionName = VK_EXT_MULTI_DRAW_EXTENSION_NAME;

  //=== VK_EXT_image_2d_view_of_3d ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImage2DViewOf3DSpecVersion   = VK_EXT_IMAGE_2D_VIEW_OF_3D_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImage2DViewOf3DExtensionName = VK_EXT_IMAGE_2D_VIEW_OF_3D_EXTENSION_NAME;

  //=== VK_KHR_portability_enumeration ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPortabilityEnumerationSpecVersion   = VK_KHR_PORTABILITY_ENUMERATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPortabilityEnumerationExtensionName = VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME;

  //=== VK_EXT_shader_tile_image ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderTileImageSpecVersion   = VK_EXT_SHADER_TILE_IMAGE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderTileImageExtensionName = VK_EXT_SHADER_TILE_IMAGE_EXTENSION_NAME;

  //=== VK_EXT_opacity_micromap ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTOpacityMicromapSpecVersion   = VK_EXT_OPACITY_MICROMAP_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTOpacityMicromapExtensionName = VK_EXT_OPACITY_MICROMAP_EXTENSION_NAME;

#if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_NV_displacement_micromap ===
  VULKAN_HPP_DEPRECATED( "The VK_NV_displacement_micromap extension has been deprecated by VK_NV_cluster_acceleration_structure." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDisplacementMicromapSpecVersion = VK_NV_DISPLACEMENT_MICROMAP_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_NV_displacement_micromap extension has been deprecated by VK_NV_cluster_acceleration_structure." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDisplacementMicromapExtensionName = VK_NV_DISPLACEMENT_MICROMAP_EXTENSION_NAME;
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_EXT_load_store_op_none ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTLoadStoreOpNoneSpecVersion   = VK_EXT_LOAD_STORE_OP_NONE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTLoadStoreOpNoneExtensionName = VK_EXT_LOAD_STORE_OP_NONE_EXTENSION_NAME;

  //=== VK_HUAWEI_cluster_culling_shader ===
  VULKAN_HPP_CONSTEXPR_INLINE auto HUAWEIClusterCullingShaderSpecVersion   = VK_HUAWEI_CLUSTER_CULLING_SHADER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto HUAWEIClusterCullingShaderExtensionName = VK_HUAWEI_CLUSTER_CULLING_SHADER_EXTENSION_NAME;

  //=== VK_EXT_border_color_swizzle ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTBorderColorSwizzleSpecVersion   = VK_EXT_BORDER_COLOR_SWIZZLE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTBorderColorSwizzleExtensionName = VK_EXT_BORDER_COLOR_SWIZZLE_EXTENSION_NAME;

  //=== VK_EXT_pageable_device_local_memory ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPageableDeviceLocalMemorySpecVersion   = VK_EXT_PAGEABLE_DEVICE_LOCAL_MEMORY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPageableDeviceLocalMemoryExtensionName = VK_EXT_PAGEABLE_DEVICE_LOCAL_MEMORY_EXTENSION_NAME;

  //=== VK_KHR_maintenance4 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance4SpecVersion   = VK_KHR_MAINTENANCE_4_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance4ExtensionName = VK_KHR_MAINTENANCE_4_EXTENSION_NAME;

  //=== VK_ARM_shader_core_properties ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMShaderCorePropertiesSpecVersion   = VK_ARM_SHADER_CORE_PROPERTIES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMShaderCorePropertiesExtensionName = VK_ARM_SHADER_CORE_PROPERTIES_EXTENSION_NAME;

  //=== VK_KHR_shader_subgroup_rotate ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderSubgroupRotateSpecVersion   = VK_KHR_SHADER_SUBGROUP_ROTATE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderSubgroupRotateExtensionName = VK_KHR_SHADER_SUBGROUP_ROTATE_EXTENSION_NAME;

  //=== VK_ARM_scheduling_controls ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMSchedulingControlsSpecVersion   = VK_ARM_SCHEDULING_CONTROLS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMSchedulingControlsExtensionName = VK_ARM_SCHEDULING_CONTROLS_EXTENSION_NAME;

  //=== VK_EXT_image_sliced_view_of_3d ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageSlicedViewOf3DSpecVersion   = VK_EXT_IMAGE_SLICED_VIEW_OF_3D_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageSlicedViewOf3DExtensionName = VK_EXT_IMAGE_SLICED_VIEW_OF_3D_EXTENSION_NAME;

  //=== VK_VALVE_descriptor_set_host_mapping ===
  VULKAN_HPP_CONSTEXPR_INLINE auto VALVEDescriptorSetHostMappingSpecVersion   = VK_VALVE_DESCRIPTOR_SET_HOST_MAPPING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto VALVEDescriptorSetHostMappingExtensionName = VK_VALVE_DESCRIPTOR_SET_HOST_MAPPING_EXTENSION_NAME;

  //=== VK_EXT_depth_clamp_zero_one ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthClampZeroOneSpecVersion   = VK_EXT_DEPTH_CLAMP_ZERO_ONE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthClampZeroOneExtensionName = VK_EXT_DEPTH_CLAMP_ZERO_ONE_EXTENSION_NAME;

  //=== VK_EXT_non_seamless_cube_map ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTNonSeamlessCubeMapSpecVersion   = VK_EXT_NON_SEAMLESS_CUBE_MAP_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTNonSeamlessCubeMapExtensionName = VK_EXT_NON_SEAMLESS_CUBE_MAP_EXTENSION_NAME;

  //=== VK_ARM_render_pass_striped ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMRenderPassStripedSpecVersion   = VK_ARM_RENDER_PASS_STRIPED_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMRenderPassStripedExtensionName = VK_ARM_RENDER_PASS_STRIPED_EXTENSION_NAME;

  //=== VK_QCOM_fragment_density_map_offset ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMFragmentDensityMapOffsetSpecVersion   = VK_QCOM_FRAGMENT_DENSITY_MAP_OFFSET_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMFragmentDensityMapOffsetExtensionName = VK_QCOM_FRAGMENT_DENSITY_MAP_OFFSET_EXTENSION_NAME;

  //=== VK_NV_copy_memory_indirect ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCopyMemoryIndirectSpecVersion   = VK_NV_COPY_MEMORY_INDIRECT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCopyMemoryIndirectExtensionName = VK_NV_COPY_MEMORY_INDIRECT_EXTENSION_NAME;

  //=== VK_NV_memory_decompression ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVMemoryDecompressionSpecVersion   = VK_NV_MEMORY_DECOMPRESSION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVMemoryDecompressionExtensionName = VK_NV_MEMORY_DECOMPRESSION_EXTENSION_NAME;

  //=== VK_NV_device_generated_commands_compute ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDeviceGeneratedCommandsComputeSpecVersion   = VK_NV_DEVICE_GENERATED_COMMANDS_COMPUTE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDeviceGeneratedCommandsComputeExtensionName = VK_NV_DEVICE_GENERATED_COMMANDS_COMPUTE_EXTENSION_NAME;

  //=== VK_NV_ray_tracing_linear_swept_spheres ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRayTracingLinearSweptSpheresSpecVersion   = VK_NV_RAY_TRACING_LINEAR_SWEPT_SPHERES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRayTracingLinearSweptSpheresExtensionName = VK_NV_RAY_TRACING_LINEAR_SWEPT_SPHERES_EXTENSION_NAME;

  //=== VK_NV_linear_color_attachment ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVLinearColorAttachmentSpecVersion   = VK_NV_LINEAR_COLOR_ATTACHMENT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVLinearColorAttachmentExtensionName = VK_NV_LINEAR_COLOR_ATTACHMENT_EXTENSION_NAME;

  //=== VK_GOOGLE_surfaceless_query ===
  VULKAN_HPP_CONSTEXPR_INLINE auto GOOGLESurfacelessQuerySpecVersion   = VK_GOOGLE_SURFACELESS_QUERY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto GOOGLESurfacelessQueryExtensionName = VK_GOOGLE_SURFACELESS_QUERY_EXTENSION_NAME;

  //=== VK_KHR_shader_maximal_reconvergence ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderMaximalReconvergenceSpecVersion   = VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderMaximalReconvergenceExtensionName = VK_KHR_SHADER_MAXIMAL_RECONVERGENCE_EXTENSION_NAME;

  //=== VK_EXT_image_compression_control_swapchain ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageCompressionControlSwapchainSpecVersion   = VK_EXT_IMAGE_COMPRESSION_CONTROL_SWAPCHAIN_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTImageCompressionControlSwapchainExtensionName = VK_EXT_IMAGE_COMPRESSION_CONTROL_SWAPCHAIN_EXTENSION_NAME;

  //=== VK_QCOM_image_processing ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMImageProcessingSpecVersion   = VK_QCOM_IMAGE_PROCESSING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMImageProcessingExtensionName = VK_QCOM_IMAGE_PROCESSING_EXTENSION_NAME;

  //=== VK_EXT_nested_command_buffer ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTNestedCommandBufferSpecVersion   = VK_EXT_NESTED_COMMAND_BUFFER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTNestedCommandBufferExtensionName = VK_EXT_NESTED_COMMAND_BUFFER_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_OHOS )
  //=== VK_OHOS_external_memory ===
  VULKAN_HPP_CONSTEXPR_INLINE auto OHOSExternalMemorySpecVersion   = VK_OHOS_EXTERNAL_MEMORY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto OHOSExternalMemoryExtensionName = VK_OHOS_EXTERNAL_MEMORY_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_OHOS*/

  //=== VK_EXT_external_memory_acquire_unmodified ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExternalMemoryAcquireUnmodifiedSpecVersion   = VK_EXT_EXTERNAL_MEMORY_ACQUIRE_UNMODIFIED_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExternalMemoryAcquireUnmodifiedExtensionName = VK_EXT_EXTERNAL_MEMORY_ACQUIRE_UNMODIFIED_EXTENSION_NAME;

  //=== VK_EXT_extended_dynamic_state3 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExtendedDynamicState3SpecVersion   = VK_EXT_EXTENDED_DYNAMIC_STATE_3_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExtendedDynamicState3ExtensionName = VK_EXT_EXTENDED_DYNAMIC_STATE_3_EXTENSION_NAME;

  //=== VK_EXT_subpass_merge_feedback ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSubpassMergeFeedbackSpecVersion   = VK_EXT_SUBPASS_MERGE_FEEDBACK_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTSubpassMergeFeedbackExtensionName = VK_EXT_SUBPASS_MERGE_FEEDBACK_EXTENSION_NAME;

  //=== VK_LUNARG_direct_driver_loading ===
  VULKAN_HPP_CONSTEXPR_INLINE auto LUNARGDirectDriverLoadingSpecVersion   = VK_LUNARG_DIRECT_DRIVER_LOADING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto LUNARGDirectDriverLoadingExtensionName = VK_LUNARG_DIRECT_DRIVER_LOADING_EXTENSION_NAME;

  //=== VK_ARM_tensors ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMTensorsSpecVersion   = VK_ARM_TENSORS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMTensorsExtensionName = VK_ARM_TENSORS_EXTENSION_NAME;

  //=== VK_EXT_shader_module_identifier ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderModuleIdentifierSpecVersion   = VK_EXT_SHADER_MODULE_IDENTIFIER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderModuleIdentifierExtensionName = VK_EXT_SHADER_MODULE_IDENTIFIER_EXTENSION_NAME;

  //=== VK_EXT_rasterization_order_attachment_access ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTRasterizationOrderAttachmentAccessSpecVersion   = VK_EXT_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTRasterizationOrderAttachmentAccessExtensionName = VK_EXT_RASTERIZATION_ORDER_ATTACHMENT_ACCESS_EXTENSION_NAME;

  //=== VK_NV_optical_flow ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVOpticalFlowSpecVersion   = VK_NV_OPTICAL_FLOW_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVOpticalFlowExtensionName = VK_NV_OPTICAL_FLOW_EXTENSION_NAME;

  //=== VK_EXT_legacy_dithering ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTLegacyDitheringSpecVersion   = VK_EXT_LEGACY_DITHERING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTLegacyDitheringExtensionName = VK_EXT_LEGACY_DITHERING_EXTENSION_NAME;

  //=== VK_EXT_pipeline_protected_access ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelineProtectedAccessSpecVersion   = VK_EXT_PIPELINE_PROTECTED_ACCESS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelineProtectedAccessExtensionName = VK_EXT_PIPELINE_PROTECTED_ACCESS_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_ANDROID_KHR )
  //=== VK_ANDROID_external_format_resolve ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ANDROIDExternalFormatResolveSpecVersion   = VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ANDROIDExternalFormatResolveExtensionName = VK_ANDROID_EXTERNAL_FORMAT_RESOLVE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_ANDROID_KHR*/

  //=== VK_KHR_maintenance5 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance5SpecVersion   = VK_KHR_MAINTENANCE_5_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance5ExtensionName = VK_KHR_MAINTENANCE_5_EXTENSION_NAME;

  //=== VK_AMD_anti_lag ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDAntiLagSpecVersion   = VK_AMD_ANTI_LAG_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDAntiLagExtensionName = VK_AMD_ANTI_LAG_EXTENSION_NAME;

#if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_AMDX_dense_geometry_format ===
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDXDenseGeometryFormatSpecVersion   = VK_AMDX_DENSE_GEOMETRY_FORMAT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto AMDXDenseGeometryFormatExtensionName = VK_AMDX_DENSE_GEOMETRY_FORMAT_EXTENSION_NAME;
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_KHR_present_id2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPresentId2SpecVersion   = VK_KHR_PRESENT_ID_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPresentId2ExtensionName = VK_KHR_PRESENT_ID_2_EXTENSION_NAME;

  //=== VK_KHR_present_wait2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPresentWait2SpecVersion   = VK_KHR_PRESENT_WAIT_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPresentWait2ExtensionName = VK_KHR_PRESENT_WAIT_2_EXTENSION_NAME;

  //=== VK_KHR_ray_tracing_position_fetch ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRayTracingPositionFetchSpecVersion   = VK_KHR_RAY_TRACING_POSITION_FETCH_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRayTracingPositionFetchExtensionName = VK_KHR_RAY_TRACING_POSITION_FETCH_EXTENSION_NAME;

  //=== VK_EXT_shader_object ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderObjectSpecVersion   = VK_EXT_SHADER_OBJECT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderObjectExtensionName = VK_EXT_SHADER_OBJECT_EXTENSION_NAME;

  //=== VK_KHR_pipeline_binary ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPipelineBinarySpecVersion   = VK_KHR_PIPELINE_BINARY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPipelineBinaryExtensionName = VK_KHR_PIPELINE_BINARY_EXTENSION_NAME;

  //=== VK_QCOM_tile_properties ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMTilePropertiesSpecVersion   = VK_QCOM_TILE_PROPERTIES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMTilePropertiesExtensionName = VK_QCOM_TILE_PROPERTIES_EXTENSION_NAME;

  //=== VK_SEC_amigo_profiling ===
  VULKAN_HPP_CONSTEXPR_INLINE auto SECAmigoProfilingSpecVersion   = VK_SEC_AMIGO_PROFILING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto SECAmigoProfilingExtensionName = VK_SEC_AMIGO_PROFILING_EXTENSION_NAME;

  //=== VK_KHR_surface_maintenance1 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSurfaceMaintenance1SpecVersion   = VK_KHR_SURFACE_MAINTENANCE_1_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSurfaceMaintenance1ExtensionName = VK_KHR_SURFACE_MAINTENANCE_1_EXTENSION_NAME;

  //=== VK_KHR_swapchain_maintenance1 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSwapchainMaintenance1SpecVersion   = VK_KHR_SWAPCHAIN_MAINTENANCE_1_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRSwapchainMaintenance1ExtensionName = VK_KHR_SWAPCHAIN_MAINTENANCE_1_EXTENSION_NAME;

  //=== VK_QCOM_multiview_per_view_viewports ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMMultiviewPerViewViewportsSpecVersion   = VK_QCOM_MULTIVIEW_PER_VIEW_VIEWPORTS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMMultiviewPerViewViewportsExtensionName = VK_QCOM_MULTIVIEW_PER_VIEW_VIEWPORTS_EXTENSION_NAME;

  //=== VK_NV_ray_tracing_invocation_reorder ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRayTracingInvocationReorderSpecVersion   = VK_NV_RAY_TRACING_INVOCATION_REORDER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRayTracingInvocationReorderExtensionName = VK_NV_RAY_TRACING_INVOCATION_REORDER_EXTENSION_NAME;

  //=== VK_NV_cooperative_vector ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCooperativeVectorSpecVersion   = VK_NV_COOPERATIVE_VECTOR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCooperativeVectorExtensionName = VK_NV_COOPERATIVE_VECTOR_EXTENSION_NAME;

  //=== VK_NV_extended_sparse_address_space ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExtendedSparseAddressSpaceSpecVersion   = VK_NV_EXTENDED_SPARSE_ADDRESS_SPACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExtendedSparseAddressSpaceExtensionName = VK_NV_EXTENDED_SPARSE_ADDRESS_SPACE_EXTENSION_NAME;

  //=== VK_EXT_mutable_descriptor_type ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMutableDescriptorTypeSpecVersion   = VK_EXT_MUTABLE_DESCRIPTOR_TYPE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMutableDescriptorTypeExtensionName = VK_EXT_MUTABLE_DESCRIPTOR_TYPE_EXTENSION_NAME;

  //=== VK_EXT_legacy_vertex_attributes ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTLegacyVertexAttributesSpecVersion   = VK_EXT_LEGACY_VERTEX_ATTRIBUTES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTLegacyVertexAttributesExtensionName = VK_EXT_LEGACY_VERTEX_ATTRIBUTES_EXTENSION_NAME;

  //=== VK_EXT_layer_settings ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTLayerSettingsSpecVersion   = VK_EXT_LAYER_SETTINGS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTLayerSettingsExtensionName = VK_EXT_LAYER_SETTINGS_EXTENSION_NAME;

  //=== VK_ARM_shader_core_builtins ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMShaderCoreBuiltinsSpecVersion   = VK_ARM_SHADER_CORE_BUILTINS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMShaderCoreBuiltinsExtensionName = VK_ARM_SHADER_CORE_BUILTINS_EXTENSION_NAME;

  //=== VK_EXT_pipeline_library_group_handles ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelineLibraryGroupHandlesSpecVersion   = VK_EXT_PIPELINE_LIBRARY_GROUP_HANDLES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPipelineLibraryGroupHandlesExtensionName = VK_EXT_PIPELINE_LIBRARY_GROUP_HANDLES_EXTENSION_NAME;

  //=== VK_EXT_dynamic_rendering_unused_attachments ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDynamicRenderingUnusedAttachmentsSpecVersion   = VK_EXT_DYNAMIC_RENDERING_UNUSED_ATTACHMENTS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDynamicRenderingUnusedAttachmentsExtensionName = VK_EXT_DYNAMIC_RENDERING_UNUSED_ATTACHMENTS_EXTENSION_NAME;

  //=== VK_KHR_internally_synchronized_queues ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRInternallySynchronizedQueuesSpecVersion   = VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRInternallySynchronizedQueuesExtensionName = VK_KHR_INTERNALLY_SYNCHRONIZED_QUEUES_EXTENSION_NAME;

  //=== VK_NV_low_latency2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVLowLatency2SpecVersion   = VK_NV_LOW_LATENCY_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVLowLatency2ExtensionName = VK_NV_LOW_LATENCY_2_EXTENSION_NAME;

  //=== VK_KHR_cooperative_matrix ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRCooperativeMatrixSpecVersion   = VK_KHR_COOPERATIVE_MATRIX_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRCooperativeMatrixExtensionName = VK_KHR_COOPERATIVE_MATRIX_EXTENSION_NAME;

  //=== VK_ARM_data_graph ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMDataGraphSpecVersion   = VK_ARM_DATA_GRAPH_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMDataGraphExtensionName = VK_ARM_DATA_GRAPH_EXTENSION_NAME;

  //=== VK_ARM_data_graph_instruction_set_tosa ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMDataGraphInstructionSetTosaSpecVersion   = VK_ARM_DATA_GRAPH_INSTRUCTION_SET_TOSA_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMDataGraphInstructionSetTosaExtensionName = VK_ARM_DATA_GRAPH_INSTRUCTION_SET_TOSA_EXTENSION_NAME;

  //=== VK_QCOM_multiview_per_view_render_areas ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMMultiviewPerViewRenderAreasSpecVersion   = VK_QCOM_MULTIVIEW_PER_VIEW_RENDER_AREAS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMMultiviewPerViewRenderAreasExtensionName = VK_QCOM_MULTIVIEW_PER_VIEW_RENDER_AREAS_EXTENSION_NAME;

  //=== VK_KHR_compute_shader_derivatives ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRComputeShaderDerivativesSpecVersion   = VK_KHR_COMPUTE_SHADER_DERIVATIVES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRComputeShaderDerivativesExtensionName = VK_KHR_COMPUTE_SHADER_DERIVATIVES_EXTENSION_NAME;

  //=== VK_KHR_video_decode_av1 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoDecodeAv1SpecVersion   = VK_KHR_VIDEO_DECODE_AV1_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoDecodeAv1ExtensionName = VK_KHR_VIDEO_DECODE_AV1_EXTENSION_NAME;

  //=== VK_KHR_video_encode_av1 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeAv1SpecVersion   = VK_KHR_VIDEO_ENCODE_AV1_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeAv1ExtensionName = VK_KHR_VIDEO_ENCODE_AV1_EXTENSION_NAME;

  //=== VK_KHR_video_decode_vp9 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoDecodeVp9SpecVersion   = VK_KHR_VIDEO_DECODE_VP9_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoDecodeVp9ExtensionName = VK_KHR_VIDEO_DECODE_VP9_EXTENSION_NAME;

  //=== VK_KHR_video_maintenance1 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoMaintenance1SpecVersion   = VK_KHR_VIDEO_MAINTENANCE_1_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoMaintenance1ExtensionName = VK_KHR_VIDEO_MAINTENANCE_1_EXTENSION_NAME;

  //=== VK_NV_per_stage_descriptor_set ===
  VULKAN_HPP_DEPRECATED( "The VK_NV_per_stage_descriptor_set extension has been deprecated by VK_EXT_descriptor_heap." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVPerStageDescriptorSetSpecVersion = VK_NV_PER_STAGE_DESCRIPTOR_SET_SPEC_VERSION;
  VULKAN_HPP_DEPRECATED( "The VK_NV_per_stage_descriptor_set extension has been deprecated by VK_EXT_descriptor_heap." )
  VULKAN_HPP_CONSTEXPR_INLINE auto NVPerStageDescriptorSetExtensionName = VK_NV_PER_STAGE_DESCRIPTOR_SET_EXTENSION_NAME;

  //=== VK_QCOM_image_processing2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMImageProcessing2SpecVersion   = VK_QCOM_IMAGE_PROCESSING_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMImageProcessing2ExtensionName = VK_QCOM_IMAGE_PROCESSING_2_EXTENSION_NAME;

  //=== VK_QCOM_filter_cubic_weights ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMFilterCubicWeightsSpecVersion   = VK_QCOM_FILTER_CUBIC_WEIGHTS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMFilterCubicWeightsExtensionName = VK_QCOM_FILTER_CUBIC_WEIGHTS_EXTENSION_NAME;

  //=== VK_QCOM_ycbcr_degamma ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMYcbcrDegammaSpecVersion   = VK_QCOM_YCBCR_DEGAMMA_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMYcbcrDegammaExtensionName = VK_QCOM_YCBCR_DEGAMMA_EXTENSION_NAME;

  //=== VK_QCOM_filter_cubic_clamp ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMFilterCubicClampSpecVersion   = VK_QCOM_FILTER_CUBIC_CLAMP_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMFilterCubicClampExtensionName = VK_QCOM_FILTER_CUBIC_CLAMP_EXTENSION_NAME;

  //=== VK_EXT_attachment_feedback_loop_dynamic_state ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTAttachmentFeedbackLoopDynamicStateSpecVersion   = VK_EXT_ATTACHMENT_FEEDBACK_LOOP_DYNAMIC_STATE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTAttachmentFeedbackLoopDynamicStateExtensionName = VK_EXT_ATTACHMENT_FEEDBACK_LOOP_DYNAMIC_STATE_EXTENSION_NAME;

  //=== VK_KHR_vertex_attribute_divisor ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVertexAttributeDivisorSpecVersion   = VK_KHR_VERTEX_ATTRIBUTE_DIVISOR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVertexAttributeDivisorExtensionName = VK_KHR_VERTEX_ATTRIBUTE_DIVISOR_EXTENSION_NAME;

  //=== VK_KHR_load_store_op_none ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRLoadStoreOpNoneSpecVersion   = VK_KHR_LOAD_STORE_OP_NONE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRLoadStoreOpNoneExtensionName = VK_KHR_LOAD_STORE_OP_NONE_EXTENSION_NAME;

  //=== VK_KHR_unified_image_layouts ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRUnifiedImageLayoutsSpecVersion   = VK_KHR_UNIFIED_IMAGE_LAYOUTS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRUnifiedImageLayoutsExtensionName = VK_KHR_UNIFIED_IMAGE_LAYOUTS_EXTENSION_NAME;

  //=== VK_KHR_shader_float_controls2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderFloatControls2SpecVersion   = VK_KHR_SHADER_FLOAT_CONTROLS_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderFloatControls2ExtensionName = VK_KHR_SHADER_FLOAT_CONTROLS_2_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_SCREEN_QNX )
  //=== VK_QNX_external_memory_screen_buffer ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QNXExternalMemoryScreenBufferSpecVersion   = VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QNXExternalMemoryScreenBufferExtensionName = VK_QNX_EXTERNAL_MEMORY_SCREEN_BUFFER_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_SCREEN_QNX*/

  //=== VK_MSFT_layered_driver ===
  VULKAN_HPP_CONSTEXPR_INLINE auto MSFTLayeredDriverSpecVersion   = VK_MSFT_LAYERED_DRIVER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto MSFTLayeredDriverExtensionName = VK_MSFT_LAYERED_DRIVER_EXTENSION_NAME;

  //=== VK_KHR_index_type_uint8 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRIndexTypeUint8SpecVersion   = VK_KHR_INDEX_TYPE_UINT8_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRIndexTypeUint8ExtensionName = VK_KHR_INDEX_TYPE_UINT8_EXTENSION_NAME;

  //=== VK_KHR_line_rasterization ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRLineRasterizationSpecVersion   = VK_KHR_LINE_RASTERIZATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRLineRasterizationExtensionName = VK_KHR_LINE_RASTERIZATION_EXTENSION_NAME;

  //=== VK_KHR_calibrated_timestamps ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRCalibratedTimestampsSpecVersion   = VK_KHR_CALIBRATED_TIMESTAMPS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRCalibratedTimestampsExtensionName = VK_KHR_CALIBRATED_TIMESTAMPS_EXTENSION_NAME;

  //=== VK_KHR_shader_expect_assume ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderExpectAssumeSpecVersion   = VK_KHR_SHADER_EXPECT_ASSUME_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderExpectAssumeExtensionName = VK_KHR_SHADER_EXPECT_ASSUME_EXTENSION_NAME;

  //=== VK_KHR_maintenance6 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance6SpecVersion   = VK_KHR_MAINTENANCE_6_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance6ExtensionName = VK_KHR_MAINTENANCE_6_EXTENSION_NAME;

  //=== VK_NV_descriptor_pool_overallocation ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDescriptorPoolOverallocationSpecVersion   = VK_NV_DESCRIPTOR_POOL_OVERALLOCATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDescriptorPoolOverallocationExtensionName = VK_NV_DESCRIPTOR_POOL_OVERALLOCATION_EXTENSION_NAME;

  //=== VK_QCOM_tile_memory_heap ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMTileMemoryHeapSpecVersion   = VK_QCOM_TILE_MEMORY_HEAP_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMTileMemoryHeapExtensionName = VK_QCOM_TILE_MEMORY_HEAP_EXTENSION_NAME;

  //=== VK_KHR_copy_memory_indirect ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRCopyMemoryIndirectSpecVersion   = VK_KHR_COPY_MEMORY_INDIRECT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRCopyMemoryIndirectExtensionName = VK_KHR_COPY_MEMORY_INDIRECT_EXTENSION_NAME;

  //=== VK_EXT_memory_decompression ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMemoryDecompressionSpecVersion   = VK_EXT_MEMORY_DECOMPRESSION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTMemoryDecompressionExtensionName = VK_EXT_MEMORY_DECOMPRESSION_EXTENSION_NAME;

  //=== VK_NV_display_stereo ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDisplayStereoSpecVersion   = VK_NV_DISPLAY_STEREO_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVDisplayStereoExtensionName = VK_NV_DISPLAY_STEREO_EXTENSION_NAME;

  //=== VK_KHR_video_encode_intra_refresh ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeIntraRefreshSpecVersion   = VK_KHR_VIDEO_ENCODE_INTRA_REFRESH_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeIntraRefreshExtensionName = VK_KHR_VIDEO_ENCODE_INTRA_REFRESH_EXTENSION_NAME;

  //=== VK_KHR_video_encode_quantization_map ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeQuantizationMapSpecVersion   = VK_KHR_VIDEO_ENCODE_QUANTIZATION_MAP_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoEncodeQuantizationMapExtensionName = VK_KHR_VIDEO_ENCODE_QUANTIZATION_MAP_EXTENSION_NAME;

  //=== VK_NV_raw_access_chains ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRawAccessChainsSpecVersion   = VK_NV_RAW_ACCESS_CHAINS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRawAccessChainsExtensionName = VK_NV_RAW_ACCESS_CHAINS_EXTENSION_NAME;

  //=== VK_NV_external_compute_queue ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExternalComputeQueueSpecVersion   = VK_NV_EXTERNAL_COMPUTE_QUEUE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVExternalComputeQueueExtensionName = VK_NV_EXTERNAL_COMPUTE_QUEUE_EXTENSION_NAME;

  //=== VK_KHR_shader_relaxed_extended_instruction ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderRelaxedExtendedInstructionSpecVersion   = VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderRelaxedExtendedInstructionExtensionName = VK_KHR_SHADER_RELAXED_EXTENDED_INSTRUCTION_EXTENSION_NAME;

  //=== VK_NV_command_buffer_inheritance ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCommandBufferInheritanceSpecVersion   = VK_NV_COMMAND_BUFFER_INHERITANCE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCommandBufferInheritanceExtensionName = VK_NV_COMMAND_BUFFER_INHERITANCE_EXTENSION_NAME;

  //=== VK_KHR_maintenance7 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance7SpecVersion   = VK_KHR_MAINTENANCE_7_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance7ExtensionName = VK_KHR_MAINTENANCE_7_EXTENSION_NAME;

  //=== VK_NV_shader_atomic_float16_vector ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVShaderAtomicFloat16VectorSpecVersion   = VK_NV_SHADER_ATOMIC_FLOAT16_VECTOR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVShaderAtomicFloat16VectorExtensionName = VK_NV_SHADER_ATOMIC_FLOAT16_VECTOR_EXTENSION_NAME;

  //=== VK_EXT_shader_replicated_composites ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderReplicatedCompositesSpecVersion   = VK_EXT_SHADER_REPLICATED_COMPOSITES_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderReplicatedCompositesExtensionName = VK_EXT_SHADER_REPLICATED_COMPOSITES_EXTENSION_NAME;

  //=== VK_EXT_shader_float8 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderFloat8SpecVersion   = VK_EXT_SHADER_FLOAT8_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderFloat8ExtensionName = VK_EXT_SHADER_FLOAT8_EXTENSION_NAME;

  //=== VK_NV_ray_tracing_validation ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRayTracingValidationSpecVersion   = VK_NV_RAY_TRACING_VALIDATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVRayTracingValidationExtensionName = VK_NV_RAY_TRACING_VALIDATION_EXTENSION_NAME;

  //=== VK_NV_cluster_acceleration_structure ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVClusterAccelerationStructureSpecVersion   = VK_NV_CLUSTER_ACCELERATION_STRUCTURE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVClusterAccelerationStructureExtensionName = VK_NV_CLUSTER_ACCELERATION_STRUCTURE_EXTENSION_NAME;

  //=== VK_NV_partitioned_acceleration_structure ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVPartitionedAccelerationStructureSpecVersion   = VK_NV_PARTITIONED_ACCELERATION_STRUCTURE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVPartitionedAccelerationStructureExtensionName = VK_NV_PARTITIONED_ACCELERATION_STRUCTURE_EXTENSION_NAME;

  //=== VK_EXT_device_generated_commands ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDeviceGeneratedCommandsSpecVersion   = VK_EXT_DEVICE_GENERATED_COMMANDS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDeviceGeneratedCommandsExtensionName = VK_EXT_DEVICE_GENERATED_COMMANDS_EXTENSION_NAME;

  //=== VK_KHR_device_fault ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDeviceFaultSpecVersion   = VK_KHR_DEVICE_FAULT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDeviceFaultExtensionName = VK_KHR_DEVICE_FAULT_EXTENSION_NAME;

  //=== VK_KHR_maintenance8 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance8SpecVersion   = VK_KHR_MAINTENANCE_8_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance8ExtensionName = VK_KHR_MAINTENANCE_8_EXTENSION_NAME;

  //=== VK_MESA_image_alignment_control ===
  VULKAN_HPP_CONSTEXPR_INLINE auto MESAImageAlignmentControlSpecVersion   = VK_MESA_IMAGE_ALIGNMENT_CONTROL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto MESAImageAlignmentControlExtensionName = VK_MESA_IMAGE_ALIGNMENT_CONTROL_EXTENSION_NAME;

  //=== VK_KHR_shader_fma ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderFmaSpecVersion   = VK_KHR_SHADER_FMA_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRShaderFmaExtensionName = VK_KHR_SHADER_FMA_EXTENSION_NAME;

  //=== VK_NV_push_constant_bank ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVPushConstantBankSpecVersion   = VK_NV_PUSH_CONSTANT_BANK_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVPushConstantBankExtensionName = VK_NV_PUSH_CONSTANT_BANK_EXTENSION_NAME;

  //=== VK_EXT_ray_tracing_invocation_reorder ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTRayTracingInvocationReorderSpecVersion   = VK_EXT_RAY_TRACING_INVOCATION_REORDER_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTRayTracingInvocationReorderExtensionName = VK_EXT_RAY_TRACING_INVOCATION_REORDER_EXTENSION_NAME;

  //=== VK_EXT_depth_clamp_control ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthClampControlSpecVersion   = VK_EXT_DEPTH_CLAMP_CONTROL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTDepthClampControlExtensionName = VK_EXT_DEPTH_CLAMP_CONTROL_EXTENSION_NAME;

  //=== VK_KHR_maintenance9 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance9SpecVersion   = VK_KHR_MAINTENANCE_9_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance9ExtensionName = VK_KHR_MAINTENANCE_9_EXTENSION_NAME;

  //=== VK_KHR_video_maintenance2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoMaintenance2SpecVersion   = VK_KHR_VIDEO_MAINTENANCE_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRVideoMaintenance2ExtensionName = VK_KHR_VIDEO_MAINTENANCE_2_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_OHOS )
  //=== VK_OHOS_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto OHOSSurfaceSpecVersion   = VK_OHOS_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto OHOSSurfaceExtensionName = VK_OHOS_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_OHOS*/

  //=== VK_HUAWEI_hdr_vivid ===
  VULKAN_HPP_CONSTEXPR_INLINE auto HUAWEIHdrVividSpecVersion   = VK_HUAWEI_HDR_VIVID_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto HUAWEIHdrVividExtensionName = VK_HUAWEI_HDR_VIVID_EXTENSION_NAME;

  //=== VK_NV_cooperative_matrix2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCooperativeMatrix2SpecVersion   = VK_NV_COOPERATIVE_MATRIX_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVCooperativeMatrix2ExtensionName = VK_NV_COOPERATIVE_MATRIX_2_EXTENSION_NAME;

  //=== VK_ARM_pipeline_opacity_micromap ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMPipelineOpacityMicromapSpecVersion   = VK_ARM_PIPELINE_OPACITY_MICROMAP_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMPipelineOpacityMicromapExtensionName = VK_ARM_PIPELINE_OPACITY_MICROMAP_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_METAL_EXT )
  //=== VK_EXT_external_memory_metal ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExternalMemoryMetalSpecVersion   = VK_EXT_EXTERNAL_MEMORY_METAL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTExternalMemoryMetalExtensionName = VK_EXT_EXTERNAL_MEMORY_METAL_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_METAL_EXT*/

  //=== VK_KHR_depth_clamp_zero_one ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDepthClampZeroOneSpecVersion   = VK_KHR_DEPTH_CLAMP_ZERO_ONE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRDepthClampZeroOneExtensionName = VK_KHR_DEPTH_CLAMP_ZERO_ONE_EXTENSION_NAME;

  //=== VK_ARM_performance_counters_by_region ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMPerformanceCountersByRegionSpecVersion   = VK_ARM_PERFORMANCE_COUNTERS_BY_REGION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMPerformanceCountersByRegionExtensionName = VK_ARM_PERFORMANCE_COUNTERS_BY_REGION_EXTENSION_NAME;

  //=== VK_ARM_shader_instrumentation ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMShaderInstrumentationSpecVersion   = VK_ARM_SHADER_INSTRUMENTATION_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMShaderInstrumentationExtensionName = VK_ARM_SHADER_INSTRUMENTATION_EXTENSION_NAME;

  //=== VK_EXT_vertex_attribute_robustness ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTVertexAttributeRobustnessSpecVersion   = VK_EXT_VERTEX_ATTRIBUTE_ROBUSTNESS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTVertexAttributeRobustnessExtensionName = VK_EXT_VERTEX_ATTRIBUTE_ROBUSTNESS_EXTENSION_NAME;

  //=== VK_ARM_format_pack ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMFormatPackSpecVersion   = VK_ARM_FORMAT_PACK_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMFormatPackExtensionName = VK_ARM_FORMAT_PACK_EXTENSION_NAME;

  //=== VK_VALVE_fragment_density_map_layered ===
  VULKAN_HPP_CONSTEXPR_INLINE auto VALVEFragmentDensityMapLayeredSpecVersion   = VK_VALVE_FRAGMENT_DENSITY_MAP_LAYERED_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto VALVEFragmentDensityMapLayeredExtensionName = VK_VALVE_FRAGMENT_DENSITY_MAP_LAYERED_EXTENSION_NAME;

  //=== VK_KHR_robustness2 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRobustness2SpecVersion   = VK_KHR_ROBUSTNESS_2_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRRobustness2ExtensionName = VK_KHR_ROBUSTNESS_2_EXTENSION_NAME;

  //=== VK_NV_present_metering ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVPresentMeteringSpecVersion   = VK_NV_PRESENT_METERING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVPresentMeteringExtensionName = VK_NV_PRESENT_METERING_EXTENSION_NAME;

  //=== VK_EXT_fragment_density_map_offset ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFragmentDensityMapOffsetSpecVersion   = VK_EXT_FRAGMENT_DENSITY_MAP_OFFSET_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTFragmentDensityMapOffsetExtensionName = VK_EXT_FRAGMENT_DENSITY_MAP_OFFSET_EXTENSION_NAME;

  //=== VK_EXT_zero_initialize_device_memory ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTZeroInitializeDeviceMemorySpecVersion   = VK_EXT_ZERO_INITIALIZE_DEVICE_MEMORY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTZeroInitializeDeviceMemoryExtensionName = VK_EXT_ZERO_INITIALIZE_DEVICE_MEMORY_EXTENSION_NAME;

  //=== VK_KHR_present_mode_fifo_latest_ready ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPresentModeFifoLatestReadySpecVersion   = VK_KHR_PRESENT_MODE_FIFO_LATEST_READY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRPresentModeFifoLatestReadyExtensionName = VK_KHR_PRESENT_MODE_FIFO_LATEST_READY_EXTENSION_NAME;

  //=== VK_KHR_opacity_micromap ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHROpacityMicromapSpecVersion   = VK_KHR_OPACITY_MICROMAP_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHROpacityMicromapExtensionName = VK_KHR_OPACITY_MICROMAP_EXTENSION_NAME;

  //=== VK_EXT_shader_64bit_indexing ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShader64BitIndexingSpecVersion   = VK_EXT_SHADER_64BIT_INDEXING_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShader64BitIndexingExtensionName = VK_EXT_SHADER_64BIT_INDEXING_EXTENSION_NAME;

  //=== VK_EXT_custom_resolve ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTCustomResolveSpecVersion   = VK_EXT_CUSTOM_RESOLVE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTCustomResolveExtensionName = VK_EXT_CUSTOM_RESOLVE_EXTENSION_NAME;

  //=== VK_QCOM_data_graph_model ===
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMDataGraphModelSpecVersion   = VK_QCOM_DATA_GRAPH_MODEL_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto QCOMDataGraphModelExtensionName = VK_QCOM_DATA_GRAPH_MODEL_EXTENSION_NAME;

  //=== VK_KHR_maintenance10 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance10SpecVersion   = VK_KHR_MAINTENANCE_10_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance10ExtensionName = VK_KHR_MAINTENANCE_10_EXTENSION_NAME;

  //=== VK_ARM_data_graph_optical_flow ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMDataGraphOpticalFlowSpecVersion   = VK_ARM_DATA_GRAPH_OPTICAL_FLOW_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMDataGraphOpticalFlowExtensionName = VK_ARM_DATA_GRAPH_OPTICAL_FLOW_EXTENSION_NAME;

  //=== VK_EXT_shader_long_vector ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderLongVectorSpecVersion   = VK_EXT_SHADER_LONG_VECTOR_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderLongVectorExtensionName = VK_EXT_SHADER_LONG_VECTOR_EXTENSION_NAME;

  //=== VK_SEC_pipeline_cache_incremental_mode ===
  VULKAN_HPP_CONSTEXPR_INLINE auto SECPipelineCacheIncrementalModeSpecVersion   = VK_SEC_PIPELINE_CACHE_INCREMENTAL_MODE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto SECPipelineCacheIncrementalModeExtensionName = VK_SEC_PIPELINE_CACHE_INCREMENTAL_MODE_EXTENSION_NAME;

  //=== VK_EXT_shader_uniform_buffer_unsized_array ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderUniformBufferUnsizedArraySpecVersion   = VK_EXT_SHADER_UNIFORM_BUFFER_UNSIZED_ARRAY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderUniformBufferUnsizedArrayExtensionName = VK_EXT_SHADER_UNIFORM_BUFFER_UNSIZED_ARRAY_EXTENSION_NAME;

  //=== VK_NV_compute_occupancy_priority ===
  VULKAN_HPP_CONSTEXPR_INLINE auto NVComputeOccupancyPrioritySpecVersion   = VK_NV_COMPUTE_OCCUPANCY_PRIORITY_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto NVComputeOccupancyPriorityExtensionName = VK_NV_COMPUTE_OCCUPANCY_PRIORITY_EXTENSION_NAME;

  //=== VK_KHR_maintenance11 ===
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance11SpecVersion   = VK_KHR_MAINTENANCE_11_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto KHRMaintenance11ExtensionName = VK_KHR_MAINTENANCE_11_EXTENSION_NAME;

  //=== VK_EXT_shader_subgroup_partitioned ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderSubgroupPartitionedSpecVersion   = VK_EXT_SHADER_SUBGROUP_PARTITIONED_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTShaderSubgroupPartitionedExtensionName = VK_EXT_SHADER_SUBGROUP_PARTITIONED_EXTENSION_NAME;

#if defined( VK_USE_PLATFORM_UBM_SEC )
  //=== VK_SEC_ubm_surface ===
  VULKAN_HPP_CONSTEXPR_INLINE auto SECUbmSurfaceSpecVersion   = VK_SEC_UBM_SURFACE_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto SECUbmSurfaceExtensionName = VK_SEC_UBM_SURFACE_EXTENSION_NAME;
#endif /*VK_USE_PLATFORM_UBM_SEC*/

  //=== VK_VALVE_shader_mixed_float_dot_product ===
  VULKAN_HPP_CONSTEXPR_INLINE auto VALVEShaderMixedFloatDotProductSpecVersion   = VK_VALVE_SHADER_MIXED_FLOAT_DOT_PRODUCT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto VALVEShaderMixedFloatDotProductExtensionName = VK_VALVE_SHADER_MIXED_FLOAT_DOT_PRODUCT_EXTENSION_NAME;

  //=== VK_SEC_throttle_hint ===
  VULKAN_HPP_CONSTEXPR_INLINE auto SECThrottleHintSpecVersion   = VK_SEC_THROTTLE_HINT_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto SECThrottleHintExtensionName = VK_SEC_THROTTLE_HINT_EXTENSION_NAME;

  //=== VK_ARM_data_graph_neural_accelerator_statistics ===
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMDataGraphNeuralAcceleratorStatisticsSpecVersion   = VK_ARM_DATA_GRAPH_NEURAL_ACCELERATOR_STATISTICS_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto ARMDataGraphNeuralAcceleratorStatisticsExtensionName = VK_ARM_DATA_GRAPH_NEURAL_ACCELERATOR_STATISTICS_EXTENSION_NAME;

  //=== VK_EXT_primitive_restart_index ===
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPrimitiveRestartIndexSpecVersion   = VK_EXT_PRIMITIVE_RESTART_INDEX_SPEC_VERSION;
  VULKAN_HPP_CONSTEXPR_INLINE auto EXTPrimitiveRestartIndexExtensionName = VK_EXT_PRIMITIVE_RESTART_INDEX_EXTENSION_NAME;

}  // namespace VULKAN_HPP_NAMESPACE

// clang-format off
#include <vulkan/vulkan_handles.hpp>
#include <vulkan/vulkan_structs.hpp>
#include <vulkan/vulkan_funcs.hpp>
// clang-format on

VULKAN_HPP_EXPORT namespace VULKAN_HPP_NAMESPACE
{
#if !defined( VULKAN_HPP_DISABLE_ENHANCED_MODE )

  //=======================
  //=== STRUCTS EXTENDS ===
  //=======================

  //=== VK_VERSION_1_0 ===
  template <>
  struct StructExtends<ShaderModuleCreateInfo, PipelineShaderStageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ShaderModuleCreateInfo, DataGraphPipelineCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineLayoutCreateInfo, BindDescriptorSetsInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineLayoutCreateInfo, PushConstantsInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineLayoutCreateInfo, PushDescriptorSetInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineLayoutCreateInfo, PushDescriptorSetWithTemplateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineLayoutCreateInfo, SetDescriptorBufferOffsetsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineLayoutCreateInfo, BindDescriptorBufferEmbeddedSamplersInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineLayoutCreateInfo, IndirectCommandsLayoutCreateInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_VERSION_1_1 ===
  template <>
  struct StructExtends<MemoryDedicatedRequirements, MemoryRequirements2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MemoryDedicatedAllocateInfo, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MemoryAllocateFlagsInfo, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceGroupCommandBufferBeginInfo, CommandBufferBeginInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceGroupSubmitInfo, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceGroupBindSparseInfo, BindSparseInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BindBufferMemoryDeviceGroupInfo, BindBufferMemoryInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BindImageMemoryDeviceGroupInfo, BindImageMemoryInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceGroupDeviceCreateInfo, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFeatures2, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageViewUsageCreateInfo, ImageViewCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceProtectedMemoryFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceProtectedMemoryFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceProtectedMemoryProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ProtectedSubmitInfo, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BindImagePlaneMemoryInfo, BindImageMemoryInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImagePlaneMemoryRequirementsInfo, ImageMemoryRequirementsInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExternalImageFormatInfo, PhysicalDeviceImageFormatInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalImageFormatProperties, ImageFormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceIDProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalMemoryImageCreateInfo, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalMemoryBufferCreateInfo, BufferCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMemoryAllocateInfo, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportFenceCreateInfo, FenceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportSemaphoreCreateInfo, SemaphoreCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSubgroupProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevice16BitStorageFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevice16BitStorageFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVariablePointersFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVariablePointersFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance3Properties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SamplerYcbcrConversionInfo, SamplerCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SamplerYcbcrConversionInfo, ImageViewCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSamplerYcbcrConversionFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSamplerYcbcrConversionFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SamplerYcbcrConversionImageFormatProperties, ImageFormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceGroupRenderPassBeginInfo, RenderPassBeginInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceGroupRenderPassBeginInfo, RenderingInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePointClippingProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassInputAttachmentAspectCreateInfo, RenderPassCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineTessellationDomainOriginStateCreateInfo, PipelineTessellationStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassMultiviewCreateInfo, RenderPassCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMultiviewFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMultiviewFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMultiviewProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderDrawParametersFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderDrawParametersFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_VERSION_1_2 ===
  template <>
  struct StructExtends<PhysicalDeviceDriverProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkan11Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkan11Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkan11Properties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkan12Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkan12Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkan12Properties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageFormatListCreateInfo, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageFormatListCreateInfo, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageFormatListCreateInfo, PhysicalDeviceImageFormatInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkanMemoryModelFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkanMemoryModelFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceHostQueryResetFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceHostQueryResetFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTimelineSemaphoreFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTimelineSemaphoreFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTimelineSemaphoreProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SemaphoreTypeCreateInfo, SemaphoreCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SemaphoreTypeCreateInfo, PhysicalDeviceExternalSemaphoreInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TimelineSemaphoreSubmitInfo, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TimelineSemaphoreSubmitInfo, BindSparseInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceBufferDeviceAddressFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceBufferDeviceAddressFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BufferOpaqueCaptureAddressCreateInfo, BufferCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MemoryOpaqueCaptureAddressAllocateInfo, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevice8BitStorageFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevice8BitStorageFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderAtomicInt64Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderAtomicInt64Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderFloat16Int8Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderFloat16Int8Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFloatControlsProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DescriptorSetLayoutBindingFlagsCreateInfo, DescriptorSetLayoutCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorIndexingFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorIndexingFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorIndexingProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DescriptorSetVariableDescriptorCountAllocateInfo, DescriptorSetAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DescriptorSetVariableDescriptorCountLayoutSupport, DescriptorSetLayoutSupport>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceScalarBlockLayoutFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceScalarBlockLayoutFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SamplerReductionModeCreateInfo, SamplerCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSamplerFilterMinmaxProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceUniformBufferStandardLayoutFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceUniformBufferStandardLayoutFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderSubgroupExtendedTypesFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderSubgroupExtendedTypesFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SubpassDescriptionDepthStencilResolve, SubpassDescription2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDepthStencilResolveProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageStencilUsageCreateInfo, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageStencilUsageCreateInfo, PhysicalDeviceImageFormatInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImagelessFramebufferFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImagelessFramebufferFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassAttachmentBeginInfo, RenderPassBeginInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FramebufferAttachmentsCreateInfo, FramebufferCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSeparateDepthStencilLayoutsFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSeparateDepthStencilLayoutsFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AttachmentReferenceStencilLayout, AttachmentReference2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AttachmentDescriptionStencilLayout, AttachmentDescription2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_VERSION_1_3 ===
  template <>
  struct StructExtends<PhysicalDeviceVulkan13Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkan13Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkan13Properties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePrivateDataFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePrivateDataFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DevicePrivateDataCreateInfo, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MemoryBarrier2, SubpassDependency2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSynchronization2Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSynchronization2Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTextureCompressionASTCHDRFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTextureCompressionASTCHDRFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FormatProperties3, FormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance4Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance4Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance4Properties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineCreationFeedbackCreateInfo, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineCreationFeedbackCreateInfo, ComputePipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineCreationFeedbackCreateInfo, RayTracingPipelineCreateInfoNV>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineCreationFeedbackCreateInfo, RayTracingPipelineCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };
#  if defined( VK_ENABLE_BETA_EXTENSIONS )
  template <>
  struct StructExtends<PipelineCreationFeedbackCreateInfo, ExecutionGraphPipelineCreateInfoAMDX>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/
  template <>
  struct StructExtends<PipelineCreationFeedbackCreateInfo, DataGraphPipelineCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderTerminateInvocationFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderTerminateInvocationFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderDemoteToHelperInvocationFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderDemoteToHelperInvocationFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineCreationCacheControlFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineCreationCacheControlFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceZeroInitializeWorkgroupMemoryFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageRobustnessFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageRobustnessFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSubgroupSizeControlFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSubgroupSizeControlFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSubgroupSizeControlProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineShaderStageRequiredSubgroupSizeCreateInfo, PipelineShaderStageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineShaderStageRequiredSubgroupSizeCreateInfo, ShaderCreateInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceInlineUniformBlockFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceInlineUniformBlockFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceInlineUniformBlockProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<WriteDescriptorSetInlineUniformBlock, WriteDescriptorSet>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DescriptorPoolInlineUniformBlockCreateInfo, DescriptorPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderIntegerDotProductFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderIntegerDotProductFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderIntegerDotProductProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTexelBufferAlignmentProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRenderingCreateInfo, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDynamicRenderingFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDynamicRenderingFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<CommandBufferInheritanceRenderingInfo, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_VERSION_1_4 ===
  template <>
  struct StructExtends<PhysicalDeviceVulkan14Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkan14Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVulkan14Properties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceQueueGlobalPriorityCreateInfo, DeviceQueueCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceGlobalPriorityQueryFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceGlobalPriorityQueryFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<QueueFamilyGlobalPriorityProperties, QueueFamilyProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceIndexTypeUint8Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceIndexTypeUint8Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance5Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance5Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance5Properties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BufferUsageFlags2CreateInfo, BufferViewCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BufferUsageFlags2CreateInfo, BufferCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BufferUsageFlags2CreateInfo, PhysicalDeviceExternalBufferInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BufferUsageFlags2CreateInfo, DescriptorBufferBindingInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance6Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance6Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance6Properties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BindMemoryStatus, BindBufferMemoryInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BindMemoryStatus, BindImageMemoryInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceHostImageCopyFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceHostImageCopyFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceHostImageCopyProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SubresourceHostMemcpySize, SubresourceLayout2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<HostImageCopyDevicePerformanceQuery, ImageFormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderSubgroupRotateFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderSubgroupRotateFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderFloatControls2Features, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderFloatControls2Features, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderExpectAssumeFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderExpectAssumeFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineCreateFlags2CreateInfo, ComputePipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineCreateFlags2CreateInfo, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineCreateFlags2CreateInfo, RayTracingPipelineCreateInfoNV>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineCreateFlags2CreateInfo, RayTracingPipelineCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePushDescriptorProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineProtectedAccessFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineProtectedAccessFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineRobustnessFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineRobustnessFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineRobustnessProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRobustnessCreateInfo, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRobustnessCreateInfo, ComputePipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRobustnessCreateInfo, PipelineShaderStageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRobustnessCreateInfo, RayTracingPipelineCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceLineRasterizationFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceLineRasterizationFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceLineRasterizationProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRasterizationLineStateCreateInfo, PipelineRasterizationStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVertexAttributeDivisorProperties, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineVertexInputDivisorStateCreateInfo, PipelineVertexInputStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVertexAttributeDivisorFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVertexAttributeDivisorFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDynamicRenderingLocalReadFeatures, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDynamicRenderingLocalReadFeatures, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderingAttachmentLocationInfo, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderingAttachmentLocationInfo, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderingInputAttachmentIndexInfo, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderingInputAttachmentIndexInfo, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_swapchain ===
  template <>
  struct StructExtends<ImageSwapchainCreateInfoKHR, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BindImageMemorySwapchainInfoKHR, BindImageMemoryInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceGroupPresentInfoKHR, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceGroupSwapchainCreateInfoKHR, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_display_swapchain ===
  template <>
  struct StructExtends<DisplayPresentInfoKHR, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_debug_report ===
  template <>
  struct StructExtends<DebugReportCallbackCreateInfoEXT, InstanceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_AMD_rasterization_order ===
  template <>
  struct StructExtends<PipelineRasterizationStateRasterizationOrderAMD, PipelineRasterizationStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_queue ===
  template <>
  struct StructExtends<QueueFamilyQueryResultStatusPropertiesKHR, QueueFamilyProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<QueueFamilyVideoPropertiesKHR, QueueFamilyProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoProfileInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoProfileListInfoKHR, PhysicalDeviceImageFormatInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoProfileListInfoKHR, PhysicalDeviceVideoFormatInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoProfileListInfoKHR, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoProfileListInfoKHR, BufferCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_decode_queue ===
  template <>
  struct StructExtends<VideoDecodeCapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeUsageInfoKHR, VideoProfileInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeUsageInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_dedicated_allocation ===
  template <>
  struct StructExtends<DedicatedAllocationImageCreateInfoNV, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DedicatedAllocationBufferCreateInfoNV, BufferCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DedicatedAllocationMemoryAllocateInfoNV, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_transform_feedback ===
  template <>
  struct StructExtends<PhysicalDeviceTransformFeedbackFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTransformFeedbackFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTransformFeedbackPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRasterizationStateStreamCreateInfoEXT, PipelineRasterizationStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NVX_binary_import ===
  template <>
  struct StructExtends<CuModuleTexturingModeCreateInfoNVX, CuModuleCreateInfoNVX>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_encode_h264 ===
  template <>
  struct StructExtends<VideoEncodeH264CapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264QualityLevelPropertiesKHR, VideoEncodeQualityLevelPropertiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264SessionCreateInfoKHR, VideoSessionCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264SessionParametersCreateInfoKHR, VideoSessionParametersCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264SessionParametersAddInfoKHR, VideoSessionParametersUpdateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264SessionParametersGetInfoKHR, VideoEncodeSessionParametersGetInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264SessionParametersFeedbackInfoKHR, VideoEncodeSessionParametersFeedbackInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264PictureInfoKHR, VideoEncodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264DpbSlotInfoKHR, VideoReferenceSlotInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264ProfileInfoKHR, VideoProfileInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264ProfileInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264RateControlInfoKHR, VideoCodingControlInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264RateControlInfoKHR, VideoBeginCodingInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264RateControlLayerInfoKHR, VideoEncodeRateControlLayerInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264GopRemainingFrameInfoKHR, VideoBeginCodingInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_encode_h265 ===
  template <>
  struct StructExtends<VideoEncodeH265CapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265SessionCreateInfoKHR, VideoSessionCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265QualityLevelPropertiesKHR, VideoEncodeQualityLevelPropertiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265SessionParametersCreateInfoKHR, VideoSessionParametersCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265SessionParametersAddInfoKHR, VideoSessionParametersUpdateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265SessionParametersGetInfoKHR, VideoEncodeSessionParametersGetInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265SessionParametersFeedbackInfoKHR, VideoEncodeSessionParametersFeedbackInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265PictureInfoKHR, VideoEncodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265DpbSlotInfoKHR, VideoReferenceSlotInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265ProfileInfoKHR, VideoProfileInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265ProfileInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265RateControlInfoKHR, VideoCodingControlInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265RateControlInfoKHR, VideoBeginCodingInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265RateControlLayerInfoKHR, VideoEncodeRateControlLayerInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265GopRemainingFrameInfoKHR, VideoBeginCodingInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_decode_h264 ===
  template <>
  struct StructExtends<VideoDecodeH264ProfileInfoKHR, VideoProfileInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH264ProfileInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH264CapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH264SessionParametersCreateInfoKHR, VideoSessionParametersCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH264SessionParametersAddInfoKHR, VideoSessionParametersUpdateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH264PictureInfoKHR, VideoDecodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH264DpbSlotInfoKHR, VideoReferenceSlotInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_AMD_texture_gather_bias_lod ===
  template <>
  struct StructExtends<TextureLODGatherFormatPropertiesAMD, ImageFormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_corner_sampled_image ===
  template <>
  struct StructExtends<PhysicalDeviceCornerSampledImageFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCornerSampledImageFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_external_memory ===
  template <>
  struct StructExtends<ExternalMemoryImageCreateInfoNV, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMemoryAllocateInfoNV, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_NV_external_memory_win32 ===
  template <>
  struct StructExtends<ImportMemoryWin32HandleInfoNV, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMemoryWin32HandleInfoNV, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_NV_win32_keyed_mutex ===
  template <>
  struct StructExtends<Win32KeyedMutexAcquireReleaseInfoNV, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<Win32KeyedMutexAcquireReleaseInfoNV, SubmitInfo2>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_EXT_validation_flags ===
  template <>
  struct StructExtends<ValidationFlagsEXT, InstanceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_astc_decode_mode ===
  template <>
  struct StructExtends<ImageViewASTCDecodeModeEXT, ImageViewCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceASTCDecodeFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceASTCDecodeFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_external_memory_win32 ===
  template <>
  struct StructExtends<ImportMemoryWin32HandleInfoKHR, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMemoryWin32HandleInfoKHR, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_external_memory_fd ===
  template <>
  struct StructExtends<ImportMemoryFdInfoKHR, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_win32_keyed_mutex ===
  template <>
  struct StructExtends<Win32KeyedMutexAcquireReleaseInfoKHR, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<Win32KeyedMutexAcquireReleaseInfoKHR, SubmitInfo2>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_external_semaphore_win32 ===
  template <>
  struct StructExtends<ExportSemaphoreWin32HandleInfoKHR, SemaphoreCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<D3D12FenceSubmitInfoKHR, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_EXT_conditional_rendering ===
  template <>
  struct StructExtends<PhysicalDeviceConditionalRenderingFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceConditionalRenderingFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<CommandBufferInheritanceConditionalRenderingInfoEXT, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_incremental_present ===
  template <>
  struct StructExtends<PresentRegionsKHR, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_clip_space_w_scaling ===
  template <>
  struct StructExtends<PipelineViewportWScalingStateCreateInfoNV, PipelineViewportStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_display_control ===
  template <>
  struct StructExtends<SwapchainCounterCreateInfoEXT, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_GOOGLE_display_timing ===
  template <>
  struct StructExtends<PresentTimesInfoGOOGLE, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NVX_multiview_per_view_attributes ===
  template <>
  struct StructExtends<PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MultiviewPerViewAttributesInfoNVX, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MultiviewPerViewAttributesInfoNVX, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MultiviewPerViewAttributesInfoNVX, RenderingInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_viewport_swizzle ===
  template <>
  struct StructExtends<PipelineViewportSwizzleStateCreateInfoNV, PipelineViewportStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_discard_rectangles ===
  template <>
  struct StructExtends<PhysicalDeviceDiscardRectanglePropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineDiscardRectangleStateCreateInfoEXT, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_conservative_rasterization ===
  template <>
  struct StructExtends<PhysicalDeviceConservativeRasterizationPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRasterizationConservativeStateCreateInfoEXT, PipelineRasterizationStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_depth_clip_enable ===
  template <>
  struct StructExtends<PhysicalDeviceDepthClipEnableFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDepthClipEnableFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRasterizationDepthClipStateCreateInfoEXT, PipelineRasterizationStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_IMG_relaxed_line_rasterization ===
  template <>
  struct StructExtends<PhysicalDeviceRelaxedLineRasterizationFeaturesIMG, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRelaxedLineRasterizationFeaturesIMG, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shared_presentable_image ===
  template <>
  struct StructExtends<SharedPresentSurfaceCapabilitiesKHR, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_KHR_external_fence_win32 ===
  template <>
  struct StructExtends<ExportFenceWin32HandleInfoKHR, FenceCreateInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_KHR_performance_query ===
  template <>
  struct StructExtends<PhysicalDevicePerformanceQueryFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePerformanceQueryFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePerformanceQueryPropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<QueryPoolPerformanceCreateInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PerformanceQuerySubmitInfoKHR, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PerformanceQuerySubmitInfoKHR, SubmitInfo2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_debug_utils ===
  template <>
  struct StructExtends<DebugUtilsMessengerCreateInfoEXT, InstanceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DebugUtilsObjectNameInfoEXT, PipelineShaderStageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DebugUtilsObjectNameInfoEXT, ResourceDescriptorInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DebugUtilsObjectNameInfoEXT, SamplerCreateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_ANDROID_KHR )
  //=== VK_ANDROID_external_memory_android_hardware_buffer ===
  template <>
  struct StructExtends<AndroidHardwareBufferUsageANDROID, ImageFormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AndroidHardwareBufferFormatPropertiesANDROID, AndroidHardwareBufferPropertiesANDROID>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImportAndroidHardwareBufferInfoANDROID, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatANDROID, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatANDROID, SamplerYcbcrConversionCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatANDROID, AttachmentDescription2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatANDROID, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatANDROID, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AndroidHardwareBufferFormatProperties2ANDROID, AndroidHardwareBufferPropertiesANDROID>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_ANDROID_KHR*/

  //=== VK_AMD_gpa_interface ===
  template <>
  struct StructExtends<PhysicalDeviceGpaFeaturesAMD, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceGpaFeaturesAMD, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceGpaPropertiesAMD, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceGpaProperties2AMD, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_AMDX_shader_enqueue ===
  template <>
  struct StructExtends<PhysicalDeviceShaderEnqueueFeaturesAMDX, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderEnqueueFeaturesAMDX, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderEnqueuePropertiesAMDX, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineShaderStageNodeCreateInfoAMDX, PipelineShaderStageCreateInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_EXT_descriptor_heap ===
  template <>
  struct StructExtends<ShaderDescriptorSetAndBindingMappingInfoEXT, PipelineShaderStageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ShaderDescriptorSetAndBindingMappingInfoEXT, ShaderCreateInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDataCreateInfoEXT, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDataCreateInfoEXT, TensorCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorHeapFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorHeapFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorHeapPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<CommandBufferInheritanceDescriptorHeapInfoEXT, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SamplerCustomBorderColorIndexCreateInfoEXT, SamplerCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<IndirectCommandsLayoutPushDataTokenNV, IndirectCommandsLayoutTokenNV>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SubsampledImageFormatPropertiesEXT, ImageFormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorHeapTensorPropertiesARM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_AMD_mixed_attachment_samples ===
  template <>
  struct StructExtends<AttachmentSampleCountInfoAMD, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AttachmentSampleCountInfoAMD, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shader_bfloat16 ===
  template <>
  struct StructExtends<PhysicalDeviceShaderBfloat16FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderBfloat16FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_sample_locations ===
  template <>
  struct StructExtends<SampleLocationsInfoEXT, ImageMemoryBarrier>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SampleLocationsInfoEXT, ImageMemoryBarrier2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassSampleLocationsBeginInfoEXT, RenderPassBeginInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineSampleLocationsStateCreateInfoEXT, PipelineMultisampleStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSampleLocationsPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_blend_operation_advanced ===
  template <>
  struct StructExtends<PhysicalDeviceBlendOperationAdvancedFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceBlendOperationAdvancedFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceBlendOperationAdvancedPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineColorBlendAdvancedStateCreateInfoEXT, PipelineColorBlendStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_fragment_coverage_to_color ===
  template <>
  struct StructExtends<PipelineCoverageToColorStateCreateInfoNV, PipelineMultisampleStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_acceleration_structure ===
  template <>
  struct StructExtends<WriteDescriptorSetAccelerationStructureKHR, WriteDescriptorSet>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceAccelerationStructureFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceAccelerationStructureFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceAccelerationStructurePropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_ray_tracing_pipeline ===
  template <>
  struct StructExtends<PhysicalDeviceRayTracingPipelineFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingPipelineFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingPipelinePropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_ray_query ===
  template <>
  struct StructExtends<PhysicalDeviceRayQueryFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayQueryFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_framebuffer_mixed_samples ===
  template <>
  struct StructExtends<PipelineCoverageModulationStateCreateInfoNV, PipelineMultisampleStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_shader_sm_builtins ===
  template <>
  struct StructExtends<PhysicalDeviceShaderSMBuiltinsPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderSMBuiltinsFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderSMBuiltinsFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_image_drm_format_modifier ===
  template <>
  struct StructExtends<DrmFormatModifierPropertiesListEXT, FormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageDrmFormatModifierInfoEXT, PhysicalDeviceImageFormatInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageDrmFormatModifierListCreateInfoEXT, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageDrmFormatModifierExplicitCreateInfoEXT, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DrmFormatModifierPropertiesList2EXT, FormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_validation_cache ===
  template <>
  struct StructExtends<ShaderModuleValidationCacheCreateInfoEXT, ShaderModuleCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ShaderModuleValidationCacheCreateInfoEXT, PipelineShaderStageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_KHR_portability_subset ===
  template <>
  struct StructExtends<PhysicalDevicePortabilitySubsetFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePortabilitySubsetFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePortabilitySubsetPropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_NV_shading_rate_image ===
  template <>
  struct StructExtends<PipelineViewportShadingRateImageStateCreateInfoNV, PipelineViewportStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShadingRateImageFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShadingRateImageFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShadingRateImagePropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineViewportCoarseSampleOrderStateCreateInfoNV, PipelineViewportStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_ray_tracing ===
  template <>
  struct StructExtends<WriteDescriptorSetAccelerationStructureNV, WriteDescriptorSet>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_representative_fragment_test ===
  template <>
  struct StructExtends<PhysicalDeviceRepresentativeFragmentTestFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRepresentativeFragmentTestFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRepresentativeFragmentTestStateCreateInfoNV, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_filter_cubic ===
  template <>
  struct StructExtends<PhysicalDeviceImageViewImageFormatInfoEXT, PhysicalDeviceImageFormatInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FilterCubicImageViewImageFormatPropertiesEXT, ImageFormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_cooperative_matrix_conversion ===
  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrixConversionFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrixConversionFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_elapsed_timer_query ===
  template <>
  struct StructExtends<PhysicalDeviceElapsedTimerQueryFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceElapsedTimerQueryFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_external_memory_host ===
  template <>
  struct StructExtends<ImportMemoryHostPointerInfoEXT, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExternalMemoryHostPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shader_clock ===
  template <>
  struct StructExtends<PhysicalDeviceShaderClockFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderClockFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_AMD_pipeline_compiler_control ===
  template <>
  struct StructExtends<PipelineCompilerControlCreateInfoAMD, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineCompilerControlCreateInfoAMD, ComputePipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };
#  if defined( VK_ENABLE_BETA_EXTENSIONS )
  template <>
  struct StructExtends<PipelineCompilerControlCreateInfoAMD, ExecutionGraphPipelineCreateInfoAMDX>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_AMD_shader_core_properties ===
  template <>
  struct StructExtends<PhysicalDeviceShaderCorePropertiesAMD, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_decode_h265 ===
  template <>
  struct StructExtends<VideoDecodeH265ProfileInfoKHR, VideoProfileInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH265ProfileInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH265CapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH265SessionParametersCreateInfoKHR, VideoSessionParametersCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH265SessionParametersAddInfoKHR, VideoSessionParametersUpdateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH265PictureInfoKHR, VideoDecodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH265DpbSlotInfoKHR, VideoReferenceSlotInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_AMD_memory_overallocation_behavior ===
  template <>
  struct StructExtends<DeviceMemoryOverallocationCreateInfoAMD, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_vertex_attribute_divisor ===
  template <>
  struct StructExtends<PhysicalDeviceVertexAttributeDivisorPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_GGP )
  //=== VK_GGP_frame_token ===
  template <>
  struct StructExtends<PresentFrameTokenGGP, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_GGP*/

  //=== VK_NV_mesh_shader ===
  template <>
  struct StructExtends<PhysicalDeviceMeshShaderFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMeshShaderFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMeshShaderPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_shader_image_footprint ===
  template <>
  struct StructExtends<PhysicalDeviceShaderImageFootprintFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderImageFootprintFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_scissor_exclusive ===
  template <>
  struct StructExtends<PipelineViewportExclusiveScissorStateCreateInfoNV, PipelineViewportStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExclusiveScissorFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExclusiveScissorFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_device_diagnostic_checkpoints ===
  template <>
  struct StructExtends<QueueFamilyCheckpointPropertiesNV, QueueFamilyProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<QueueFamilyCheckpointProperties2NV, QueueFamilyProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_present_timing ===
  template <>
  struct StructExtends<PhysicalDevicePresentTimingFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentTimingFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PresentTimingSurfaceCapabilitiesEXT, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SwapchainCalibratedTimestampInfoEXT, CalibratedTimestampInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PresentTimingsInfoEXT, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_INTEL_shader_integer_functions2 ===
  template <>
  struct StructExtends<PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_INTEL_performance_query ===
  template <>
  struct StructExtends<QueryPoolPerformanceQueryCreateInfoINTEL, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_pci_bus_info ===
  template <>
  struct StructExtends<PhysicalDevicePCIBusInfoPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_AMD_display_native_hdr ===
  template <>
  struct StructExtends<DisplayNativeHdrSurfaceCapabilitiesAMD, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SwapchainDisplayNativeHdrCreateInfoAMD, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_fragment_density_map ===
  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMapFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMapFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMapPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassFragmentDensityMapCreateInfoEXT, RenderPassCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassFragmentDensityMapCreateInfoEXT, RenderPassCreateInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderingFragmentDensityMapAttachmentInfoEXT, RenderingInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_fragment_shading_rate ===
  template <>
  struct StructExtends<FragmentShadingRateAttachmentInfoKHR, SubpassDescription2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineFragmentShadingRateStateCreateInfoKHR, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentShadingRateFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentShadingRateFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentShadingRatePropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderingFragmentShadingRateAttachmentInfoKHR, RenderingInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_AMD_shader_core_properties2 ===
  template <>
  struct StructExtends<PhysicalDeviceShaderCoreProperties2AMD, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_AMD_device_coherent_memory ===
  template <>
  struct StructExtends<PhysicalDeviceCoherentMemoryFeaturesAMD, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCoherentMemoryFeaturesAMD, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shader_constant_data ===
  template <>
  struct StructExtends<PhysicalDeviceShaderConstantDataFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderConstantDataFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shader_abort ===
  template <>
  struct StructExtends<PhysicalDeviceShaderAbortFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderAbortFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceFaultShaderAbortMessageInfoKHR, DeviceFaultDebugInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderAbortPropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_image_atomic_int64 ===
  template <>
  struct StructExtends<PhysicalDeviceShaderImageAtomicInt64FeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderImageAtomicInt64FeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shader_quad_control ===
  template <>
  struct StructExtends<PhysicalDeviceShaderQuadControlFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderQuadControlFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_memory_budget ===
  template <>
  struct StructExtends<PhysicalDeviceMemoryBudgetPropertiesEXT, PhysicalDeviceMemoryProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_memory_priority ===
  template <>
  struct StructExtends<PhysicalDeviceMemoryPriorityFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMemoryPriorityFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MemoryPriorityAllocateInfoEXT, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_surface_protected_capabilities ===
  template <>
  struct StructExtends<SurfaceProtectedCapabilitiesKHR, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_dedicated_allocation_image_aliasing ===
  template <>
  struct StructExtends<PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_buffer_device_address ===
  template <>
  struct StructExtends<PhysicalDeviceBufferDeviceAddressFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceBufferDeviceAddressFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BufferDeviceAddressCreateInfoEXT, BufferCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_validation_features ===
  template <>
  struct StructExtends<ValidationFeaturesEXT, InstanceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ValidationFeaturesEXT, ShaderModuleCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ValidationFeaturesEXT, ShaderCreateInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_present_wait ===
  template <>
  struct StructExtends<PhysicalDevicePresentWaitFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentWaitFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_cooperative_matrix ===
  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrixFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrixFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrixPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_coverage_reduction_mode ===
  template <>
  struct StructExtends<PhysicalDeviceCoverageReductionModeFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCoverageReductionModeFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineCoverageReductionStateCreateInfoNV, PipelineMultisampleStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_fragment_shader_interlock ===
  template <>
  struct StructExtends<PhysicalDeviceFragmentShaderInterlockFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentShaderInterlockFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_ycbcr_image_arrays ===
  template <>
  struct StructExtends<PhysicalDeviceYcbcrImageArraysFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceYcbcrImageArraysFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_provoking_vertex ===
  template <>
  struct StructExtends<PhysicalDeviceProvokingVertexFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceProvokingVertexFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceProvokingVertexPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineRasterizationProvokingVertexStateCreateInfoEXT, PipelineRasterizationStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_WIN32_KHR )
  //=== VK_EXT_full_screen_exclusive ===
  template <>
  struct StructExtends<SurfaceFullScreenExclusiveInfoEXT, PhysicalDeviceSurfaceInfo2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SurfaceFullScreenExclusiveInfoEXT, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SurfaceCapabilitiesFullScreenExclusiveEXT, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SurfaceFullScreenExclusiveWin32InfoEXT, PhysicalDeviceSurfaceInfo2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SurfaceFullScreenExclusiveWin32InfoEXT, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_WIN32_KHR*/

  //=== VK_EXT_shader_atomic_float ===
  template <>
  struct StructExtends<PhysicalDeviceShaderAtomicFloatFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderAtomicFloatFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_extended_dynamic_state ===
  template <>
  struct StructExtends<PhysicalDeviceExtendedDynamicStateFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExtendedDynamicStateFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_pipeline_executable_properties ===
  template <>
  struct StructExtends<PhysicalDevicePipelineExecutablePropertiesFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineExecutablePropertiesFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_map_memory_placed ===
  template <>
  struct StructExtends<PhysicalDeviceMapMemoryPlacedFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMapMemoryPlacedFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMapMemoryPlacedPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MemoryMapPlacedInfoEXT, MemoryMapInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_atomic_float2 ===
  template <>
  struct StructExtends<PhysicalDeviceShaderAtomicFloat2FeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderAtomicFloat2FeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_device_generated_commands ===
  template <>
  struct StructExtends<PhysicalDeviceDeviceGeneratedCommandsPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDeviceGeneratedCommandsFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDeviceGeneratedCommandsFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<GraphicsPipelineShaderGroupsCreateInfoNV, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_inherited_viewport_scissor ===
  template <>
  struct StructExtends<PhysicalDeviceInheritedViewportScissorFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceInheritedViewportScissorFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<CommandBufferInheritanceViewportScissorInfoNV, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_texel_buffer_alignment ===
  template <>
  struct StructExtends<PhysicalDeviceTexelBufferAlignmentFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTexelBufferAlignmentFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_render_pass_transform ===
  template <>
  struct StructExtends<RenderPassTransformBeginInfoQCOM, RenderPassBeginInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<CommandBufferInheritanceRenderPassTransformInfoQCOM, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_depth_bias_control ===
  template <>
  struct StructExtends<PhysicalDeviceDepthBiasControlFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDepthBiasControlFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DepthBiasRepresentationInfoEXT, DepthBiasInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DepthBiasRepresentationInfoEXT, PipelineRasterizationStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_device_memory_report ===
  template <>
  struct StructExtends<PhysicalDeviceDeviceMemoryReportFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDeviceMemoryReportFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceDeviceMemoryReportCreateInfoEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_custom_border_color ===
  template <>
  struct StructExtends<SamplerCustomBorderColorCreateInfoEXT, SamplerCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCustomBorderColorPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCustomBorderColorFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCustomBorderColorFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_texture_compression_astc_3d ===
  template <>
  struct StructExtends<PhysicalDeviceTextureCompressionASTC3DFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTextureCompressionASTC3DFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_pipeline_library ===
  template <>
  struct StructExtends<PipelineLibraryCreateInfoKHR, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_present_barrier ===
  template <>
  struct StructExtends<PhysicalDevicePresentBarrierFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentBarrierFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SurfaceCapabilitiesPresentBarrierNV, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SwapchainPresentBarrierCreateInfoNV, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_present_id ===
  template <>
  struct StructExtends<PresentIdKHR, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentIdFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentIdFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_encode_queue ===
  template <>
  struct StructExtends<VideoEncodeCapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<QueryPoolVideoEncodeFeedbackCreateInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeUsageInfoKHR, VideoProfileInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeUsageInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeRateControlInfoKHR, VideoCodingControlInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeRateControlInfoKHR, VideoBeginCodingInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeQualityLevelInfoKHR, VideoCodingControlInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeQualityLevelInfoKHR, VideoSessionParametersCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_device_diagnostics_config ===
  template <>
  struct StructExtends<PhysicalDeviceDiagnosticsConfigFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDiagnosticsConfigFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceDiagnosticsConfigCreateInfoNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_queue_perf_hint ===
  template <>
  struct StructExtends<PhysicalDeviceQueuePerfHintFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceQueuePerfHintFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceQueuePerfHintPropertiesQCOM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_image_processing3 ===
  template <>
  struct StructExtends<PhysicalDeviceImageProcessing3FeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageProcessing3FeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_shader_multiple_wait_queues ===
  template <>
  struct StructExtends<PhysicalDeviceShaderMultipleWaitQueuesFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderMultipleWaitQueuesFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderMultipleWaitQueuesPropertiesQCOM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_split_barrier ===
  template <>
  struct StructExtends<PhysicalDeviceShaderSplitBarrierFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderSplitBarrierFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderSplitBarrierPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_NV_cuda_kernel_launch ===
  template <>
  struct StructExtends<PhysicalDeviceCudaKernelLaunchFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCudaKernelLaunchFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCudaKernelLaunchPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_QCOM_tile_shading ===
  template <>
  struct StructExtends<PhysicalDeviceTileShadingFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTileShadingFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTileShadingPropertiesQCOM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassTileShadingCreateInfoQCOM, RenderPassCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassTileShadingCreateInfoQCOM, RenderPassCreateInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassTileShadingCreateInfoQCOM, RenderingInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassTileShadingCreateInfoQCOM, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_low_latency ===
  template <>
  struct StructExtends<QueryLowLatencySupportNV, SemaphoreCreateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_METAL_EXT )
  //=== VK_EXT_metal_objects ===
  template <>
  struct StructExtends<ExportMetalObjectCreateInfoEXT, InstanceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalObjectCreateInfoEXT, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalObjectCreateInfoEXT, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalObjectCreateInfoEXT, ImageViewCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalObjectCreateInfoEXT, BufferViewCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalObjectCreateInfoEXT, SemaphoreCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalObjectCreateInfoEXT, EventCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalDeviceInfoEXT, ExportMetalObjectsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalCommandQueueInfoEXT, ExportMetalObjectsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalBufferInfoEXT, ExportMetalObjectsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImportMetalBufferInfoEXT, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalTextureInfoEXT, ExportMetalObjectsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImportMetalTextureInfoEXT, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalIOSurfaceInfoEXT, ExportMetalObjectsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImportMetalIOSurfaceInfoEXT, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExportMetalSharedEventInfoEXT, ExportMetalObjectsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImportMetalSharedEventInfoEXT, SemaphoreCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImportMetalSharedEventInfoEXT, EventCreateInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_METAL_EXT*/

  //=== VK_EXT_descriptor_buffer ===
  template <>
  struct StructExtends<PhysicalDeviceDescriptorBufferPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorBufferFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorBufferFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DescriptorBufferBindingPushDescriptorBufferHandleEXT, DescriptorBufferBindingInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDescriptorDataCreateInfoEXT, BufferCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDescriptorDataCreateInfoEXT, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDescriptorDataCreateInfoEXT, ImageViewCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDescriptorDataCreateInfoEXT, SamplerCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDescriptorDataCreateInfoEXT, AccelerationStructureCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDescriptorDataCreateInfoEXT, AccelerationStructureCreateInfoNV>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDescriptorDataCreateInfoEXT, TensorCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDescriptorDataCreateInfoEXT, TensorViewCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpaqueCaptureDescriptorDataCreateInfoEXT, AccelerationStructureCreateInfo2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorBufferDensityMapPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_device_address_commands ===
  template <>
  struct StructExtends<MemoryRangeBarriersInfoKHR, DependencyInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDeviceAddressCommandsFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDeviceAddressCommandsFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_graphics_pipeline_library ===
  template <>
  struct StructExtends<PhysicalDeviceGraphicsPipelineLibraryFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceGraphicsPipelineLibraryFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceGraphicsPipelineLibraryPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<GraphicsPipelineLibraryCreateInfoEXT, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_AMD_shader_early_and_late_fragment_tests ===
  template <>
  struct StructExtends<PhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderEarlyAndLateFragmentTestsFeaturesAMD, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_fragment_shader_barycentric ===
  template <>
  struct StructExtends<PhysicalDeviceFragmentShaderBarycentricFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentShaderBarycentricFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentShaderBarycentricPropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shader_subgroup_uniform_control_flow ===
  template <>
  struct StructExtends<PhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderSubgroupUniformControlFlowFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_fragment_shading_rate_enums ===
  template <>
  struct StructExtends<PhysicalDeviceFragmentShadingRateEnumsFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentShadingRateEnumsFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentShadingRateEnumsPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineFragmentShadingRateEnumStateCreateInfoNV, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_ray_tracing_motion_blur ===
  template <>
  struct StructExtends<AccelerationStructureGeometryMotionTrianglesDataNV, AccelerationStructureGeometryTrianglesDataKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AccelerationStructureMotionInfoNV, AccelerationStructureCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingMotionBlurFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingMotionBlurFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_mesh_shader ===
  template <>
  struct StructExtends<PhysicalDeviceMeshShaderFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMeshShaderFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMeshShaderPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_ycbcr_2plane_444_formats ===
  template <>
  struct StructExtends<PhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceYcbcr2Plane444FormatsFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_fragment_density_map2 ===
  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMap2FeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMap2FeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMap2PropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_rotated_copy_commands ===
  template <>
  struct StructExtends<CopyCommandTransformInfoQCOM, BufferImageCopy2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<CopyCommandTransformInfoQCOM, ImageBlit2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<CopyCommandTransformInfoQCOM, DeviceMemoryImageCopyKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_workgroup_memory_explicit_layout ===
  template <>
  struct StructExtends<PhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceWorkgroupMemoryExplicitLayoutFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_image_compression_control ===
  template <>
  struct StructExtends<PhysicalDeviceImageCompressionControlFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageCompressionControlFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageCompressionControlEXT, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageCompressionControlEXT, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageCompressionControlEXT, PhysicalDeviceImageFormatInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageCompressionPropertiesEXT, ImageFormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageCompressionPropertiesEXT, SurfaceFormat2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageCompressionPropertiesEXT, SubresourceLayout2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_attachment_feedback_loop_layout ===
  template <>
  struct StructExtends<PhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceAttachmentFeedbackLoopLayoutFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_4444_formats ===
  template <>
  struct StructExtends<PhysicalDevice4444FormatsFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevice4444FormatsFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_device_fault ===
  template <>
  struct StructExtends<PhysicalDeviceFaultFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFaultFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_rgba10x6_formats ===
  template <>
  struct StructExtends<PhysicalDeviceRGBA10X6FormatsFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRGBA10X6FormatsFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_vertex_input_dynamic_state ===
  template <>
  struct StructExtends<PhysicalDeviceVertexInputDynamicStateFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVertexInputDynamicStateFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_physical_device_drm ===
  template <>
  struct StructExtends<PhysicalDeviceDrmPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_device_address_binding_report ===
  template <>
  struct StructExtends<PhysicalDeviceAddressBindingReportFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceAddressBindingReportFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceAddressBindingCallbackDataEXT, DebugUtilsMessengerCallbackDataEXT>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_depth_clip_control ===
  template <>
  struct StructExtends<PhysicalDeviceDepthClipControlFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDepthClipControlFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineViewportDepthClipControlCreateInfoEXT, PipelineViewportStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_primitive_topology_list_restart ===
  template <>
  struct StructExtends<PhysicalDevicePrimitiveTopologyListRestartFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePrimitiveTopologyListRestartFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_FUCHSIA )
  //=== VK_FUCHSIA_external_memory ===
  template <>
  struct StructExtends<ImportMemoryZirconHandleInfoFUCHSIA, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_FUCHSIA*/

#  if defined( VK_USE_PLATFORM_FUCHSIA )
  //=== VK_FUCHSIA_buffer_collection ===
  template <>
  struct StructExtends<ImportMemoryBufferCollectionFUCHSIA, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BufferCollectionImageCreateInfoFUCHSIA, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BufferCollectionBufferCreateInfoFUCHSIA, BufferCreateInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_FUCHSIA*/

  //=== VK_HUAWEI_subpass_shading ===
  template <>
  struct StructExtends<SubpassShadingPipelineCreateInfoHUAWEI, ComputePipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSubpassShadingFeaturesHUAWEI, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSubpassShadingFeaturesHUAWEI, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSubpassShadingPropertiesHUAWEI, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_HUAWEI_invocation_mask ===
  template <>
  struct StructExtends<PhysicalDeviceInvocationMaskFeaturesHUAWEI, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceInvocationMaskFeaturesHUAWEI, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_external_memory_rdma ===
  template <>
  struct StructExtends<PhysicalDeviceExternalMemoryRDMAFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExternalMemoryRDMAFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_pipeline_properties ===
  template <>
  struct StructExtends<PhysicalDevicePipelinePropertiesFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelinePropertiesFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_frame_boundary ===
  template <>
  struct StructExtends<PhysicalDeviceFrameBoundaryFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFrameBoundaryFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FrameBoundaryEXT, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FrameBoundaryEXT, SubmitInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FrameBoundaryEXT, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FrameBoundaryEXT, BindSparseInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_multisampled_render_to_single_sampled ===
  template <>
  struct StructExtends<PhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMultisampledRenderToSingleSampledFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SubpassResolvePerformanceQueryEXT, FormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MultisampledRenderToSingleSampledInfoEXT, SubpassDescription2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MultisampledRenderToSingleSampledInfoEXT, RenderingInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_extended_dynamic_state2 ===
  template <>
  struct StructExtends<PhysicalDeviceExtendedDynamicState2FeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExtendedDynamicState2FeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_color_write_enable ===
  template <>
  struct StructExtends<PhysicalDeviceColorWriteEnableFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceColorWriteEnableFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineColorWriteCreateInfoEXT, PipelineColorBlendStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_primitives_generated_query ===
  template <>
  struct StructExtends<PhysicalDevicePrimitivesGeneratedQueryFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePrimitivesGeneratedQueryFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_ray_tracing_maintenance1 ===
  template <>
  struct StructExtends<PhysicalDeviceRayTracingMaintenance1FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingMaintenance1FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shader_untyped_pointers ===
  template <>
  struct StructExtends<PhysicalDeviceShaderUntypedPointersFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderUntypedPointersFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_VALVE_video_encode_rgb_conversion ===
  template <>
  struct StructExtends<PhysicalDeviceVideoEncodeRgbConversionFeaturesVALVE, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVideoEncodeRgbConversionFeaturesVALVE, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeRgbConversionCapabilitiesVALVE, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeProfileRgbConversionInfoVALVE, VideoProfileInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeSessionRgbConversionCreateInfoVALVE, VideoSessionCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_image_view_min_lod ===
  template <>
  struct StructExtends<PhysicalDeviceImageViewMinLodFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageViewMinLodFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageViewMinLodCreateInfoEXT, ImageViewCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_multi_draw ===
  template <>
  struct StructExtends<PhysicalDeviceMultiDrawFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMultiDrawFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMultiDrawPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_image_2d_view_of_3d ===
  template <>
  struct StructExtends<PhysicalDeviceImage2DViewOf3DFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImage2DViewOf3DFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_tile_image ===
  template <>
  struct StructExtends<PhysicalDeviceShaderTileImageFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderTileImageFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderTileImagePropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_opacity_micromap ===
  template <>
  struct StructExtends<PhysicalDeviceOpacityMicromapFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceOpacityMicromapFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceOpacityMicromapPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AccelerationStructureTrianglesOpacityMicromapEXT, AccelerationStructureGeometryTrianglesDataKHR>
  {
    enum
    {
      value = true
    };
  };
#  if defined( VK_ENABLE_BETA_EXTENSIONS )
  template <>
  struct StructExtends<AccelerationStructureTrianglesOpacityMicromapEXT, AccelerationStructureDenseGeometryFormatTrianglesDataAMDX>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_NV_displacement_micromap ===
  template <>
  struct StructExtends<PhysicalDeviceDisplacementMicromapFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDisplacementMicromapFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDisplacementMicromapPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AccelerationStructureTrianglesDisplacementMicromapNV, AccelerationStructureGeometryTrianglesDataKHR>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_HUAWEI_cluster_culling_shader ===
  template <>
  struct StructExtends<PhysicalDeviceClusterCullingShaderFeaturesHUAWEI, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceClusterCullingShaderFeaturesHUAWEI, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceClusterCullingShaderPropertiesHUAWEI, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceClusterCullingShaderVrsFeaturesHUAWEI, PhysicalDeviceClusterCullingShaderFeaturesHUAWEI>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_border_color_swizzle ===
  template <>
  struct StructExtends<PhysicalDeviceBorderColorSwizzleFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceBorderColorSwizzleFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SamplerBorderColorComponentMappingCreateInfoEXT, SamplerCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_pageable_device_local_memory ===
  template <>
  struct StructExtends<PhysicalDevicePageableDeviceLocalMemoryFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePageableDeviceLocalMemoryFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_shader_core_properties ===
  template <>
  struct StructExtends<PhysicalDeviceShaderCorePropertiesARM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_scheduling_controls ===
  template <>
  struct StructExtends<DeviceQueueShaderCoreControlCreateInfoARM, DeviceQueueCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DeviceQueueShaderCoreControlCreateInfoARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSchedulingControlsFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSchedulingControlsFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSchedulingControlsPropertiesARM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSchedulingControlsDispatchParametersPropertiesARM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_image_sliced_view_of_3d ===
  template <>
  struct StructExtends<PhysicalDeviceImageSlicedViewOf3DFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageSlicedViewOf3DFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageViewSlicedCreateInfoEXT, ImageViewCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_VALVE_descriptor_set_host_mapping ===
  template <>
  struct StructExtends<PhysicalDeviceDescriptorSetHostMappingFeaturesVALVE, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorSetHostMappingFeaturesVALVE, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_non_seamless_cube_map ===
  template <>
  struct StructExtends<PhysicalDeviceNonSeamlessCubeMapFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceNonSeamlessCubeMapFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_render_pass_striped ===
  template <>
  struct StructExtends<PhysicalDeviceRenderPassStripedFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRenderPassStripedFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRenderPassStripedPropertiesARM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassStripeBeginInfoARM, RenderingInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassStripeBeginInfoARM, RenderPassBeginInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassStripeSubmitInfoARM, CommandBufferSubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_copy_memory_indirect ===
  template <>
  struct StructExtends<PhysicalDeviceCopyMemoryIndirectFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCopyMemoryIndirectFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_device_generated_commands_compute ===
  template <>
  struct StructExtends<PhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDeviceGeneratedCommandsComputeFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ComputePipelineIndirectBufferInfoNV, ComputePipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_ray_tracing_linear_swept_spheres ===
  template <>
  struct StructExtends<PhysicalDeviceRayTracingLinearSweptSpheresFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingLinearSweptSpheresFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AccelerationStructureGeometryLinearSweptSpheresDataNV, AccelerationStructureGeometryKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AccelerationStructureGeometrySpheresDataNV, AccelerationStructureGeometryKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_linear_color_attachment ===
  template <>
  struct StructExtends<PhysicalDeviceLinearColorAttachmentFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceLinearColorAttachmentFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shader_maximal_reconvergence ===
  template <>
  struct StructExtends<PhysicalDeviceShaderMaximalReconvergenceFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderMaximalReconvergenceFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_image_compression_control_swapchain ===
  template <>
  struct StructExtends<PhysicalDeviceImageCompressionControlSwapchainFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageCompressionControlSwapchainFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_image_processing ===
  template <>
  struct StructExtends<ImageViewSampleWeightCreateInfoQCOM, ImageViewCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageProcessingFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageProcessingFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageProcessingPropertiesQCOM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_nested_command_buffer ===
  template <>
  struct StructExtends<PhysicalDeviceNestedCommandBufferFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceNestedCommandBufferFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceNestedCommandBufferPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_OHOS )
  //=== VK_OHOS_external_memory ===
  template <>
  struct StructExtends<NativeBufferUsageOHOS, ImageFormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<NativeBufferFormatPropertiesOHOS, NativeBufferPropertiesOHOS>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImportNativeBufferInfoOHOS, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatOHOS, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatOHOS, SamplerYcbcrConversionCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatOHOS, AttachmentDescription2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatOHOS, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatOHOS, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_OHOS*/

  //=== VK_EXT_external_memory_acquire_unmodified ===
  template <>
  struct StructExtends<ExternalMemoryAcquireUnmodifiedEXT, BufferMemoryBarrier>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalMemoryAcquireUnmodifiedEXT, BufferMemoryBarrier2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalMemoryAcquireUnmodifiedEXT, ImageMemoryBarrier>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalMemoryAcquireUnmodifiedEXT, ImageMemoryBarrier2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_extended_dynamic_state3 ===
  template <>
  struct StructExtends<PhysicalDeviceExtendedDynamicState3FeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExtendedDynamicState3FeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExtendedDynamicState3PropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_subpass_merge_feedback ===
  template <>
  struct StructExtends<PhysicalDeviceSubpassMergeFeedbackFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSubpassMergeFeedbackFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassCreationControlEXT, RenderPassCreateInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassCreationControlEXT, SubpassDescription2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassCreationFeedbackCreateInfoEXT, RenderPassCreateInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassSubpassFeedbackCreateInfoEXT, SubpassDescription2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_LUNARG_direct_driver_loading ===
  template <>
  struct StructExtends<DirectDriverLoadingListLUNARG, InstanceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_tensors ===
  template <>
  struct StructExtends<TensorDescriptionARM, DataGraphPipelineResourceInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TensorDescriptionARM, DataGraphPipelineConstantARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<WriteDescriptorSetTensorARM, WriteDescriptorSet>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TensorFormatPropertiesARM, FormatProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTensorPropertiesARM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TensorMemoryBarrierARM, DependencyInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TensorDependencyInfoARM, DependencyInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTensorFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTensorFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MemoryDedicatedAllocateInfoTensorARM, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalMemoryTensorCreateInfoARM, TensorCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorBufferTensorFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorBufferTensorFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorBufferTensorPropertiesARM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DescriptorGetTensorInfoARM, DescriptorGetInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FrameBoundaryTensorsARM, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FrameBoundaryTensorsARM, SubmitInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FrameBoundaryTensorsARM, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<FrameBoundaryTensorsARM, BindSparseInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_module_identifier ===
  template <>
  struct StructExtends<PhysicalDeviceShaderModuleIdentifierFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderModuleIdentifierFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderModuleIdentifierPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineShaderStageModuleIdentifierCreateInfoEXT, PipelineShaderStageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_rasterization_order_attachment_access ===
  template <>
  struct StructExtends<PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRasterizationOrderAttachmentAccessFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_optical_flow ===
  template <>
  struct StructExtends<PhysicalDeviceOpticalFlowFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceOpticalFlowFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceOpticalFlowPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpticalFlowImageFormatInfoNV, PhysicalDeviceImageFormatInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpticalFlowImageFormatInfoNV, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<OpticalFlowSessionCreatePrivateDataInfoNV, OpticalFlowSessionCreateInfoNV>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_legacy_dithering ===
  template <>
  struct StructExtends<PhysicalDeviceLegacyDitheringFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceLegacyDitheringFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_ANDROID_KHR )
  //=== VK_ANDROID_external_format_resolve ===
  template <>
  struct StructExtends<PhysicalDeviceExternalFormatResolveFeaturesANDROID, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExternalFormatResolveFeaturesANDROID, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExternalFormatResolvePropertiesANDROID, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AndroidHardwareBufferFormatResolvePropertiesANDROID, AndroidHardwareBufferPropertiesANDROID>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_ANDROID_KHR*/

  //=== VK_AMD_anti_lag ===
  template <>
  struct StructExtends<PhysicalDeviceAntiLagFeaturesAMD, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceAntiLagFeaturesAMD, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_ENABLE_BETA_EXTENSIONS )
  //=== VK_AMDX_dense_geometry_format ===
  template <>
  struct StructExtends<PhysicalDeviceDenseGeometryFormatFeaturesAMDX, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDenseGeometryFormatFeaturesAMDX, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AccelerationStructureDenseGeometryFormatTrianglesDataAMDX, AccelerationStructureGeometryKHR>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_KHR_present_id2 ===
  template <>
  struct StructExtends<SurfaceCapabilitiesPresentId2KHR, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PresentId2KHR, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentId2FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentId2FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_present_wait2 ===
  template <>
  struct StructExtends<SurfaceCapabilitiesPresentWait2KHR, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentWait2FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentWait2FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_ray_tracing_position_fetch ===
  template <>
  struct StructExtends<PhysicalDeviceRayTracingPositionFetchFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingPositionFetchFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_object ===
  template <>
  struct StructExtends<PhysicalDeviceShaderObjectFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderObjectFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderObjectPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_pipeline_binary ===
  template <>
  struct StructExtends<PhysicalDevicePipelineBinaryFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineBinaryFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineBinaryPropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DevicePipelineBinaryInternalCacheControlKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineBinaryInfoKHR, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineBinaryInfoKHR, ComputePipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineBinaryInfoKHR, RayTracingPipelineCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_tile_properties ===
  template <>
  struct StructExtends<PhysicalDeviceTilePropertiesFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTilePropertiesFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_SEC_amigo_profiling ===
  template <>
  struct StructExtends<PhysicalDeviceAmigoProfilingFeaturesSEC, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceAmigoProfilingFeaturesSEC, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AmigoProfilingSubmitInfoSEC, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_surface_maintenance1 ===
  template <>
  struct StructExtends<SurfacePresentModeKHR, PhysicalDeviceSurfaceInfo2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SurfacePresentScalingCapabilitiesKHR, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SurfacePresentModeCompatibilityKHR, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_swapchain_maintenance1 ===
  template <>
  struct StructExtends<PhysicalDeviceSwapchainMaintenance1FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceSwapchainMaintenance1FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SwapchainPresentFenceInfoKHR, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SwapchainPresentModesCreateInfoKHR, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SwapchainPresentModeInfoKHR, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SwapchainPresentScalingCreateInfoKHR, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_multiview_per_view_viewports ===
  template <>
  struct StructExtends<PhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMultiviewPerViewViewportsFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_ray_tracing_invocation_reorder ===
  template <>
  struct StructExtends<PhysicalDeviceRayTracingInvocationReorderPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingInvocationReorderFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingInvocationReorderFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_cooperative_vector ===
  template <>
  struct StructExtends<PhysicalDeviceCooperativeVectorPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCooperativeVectorFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCooperativeVectorFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_extended_sparse_address_space ===
  template <>
  struct StructExtends<PhysicalDeviceExtendedSparseAddressSpaceFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExtendedSparseAddressSpaceFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExtendedSparseAddressSpacePropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_mutable_descriptor_type ===
  template <>
  struct StructExtends<PhysicalDeviceMutableDescriptorTypeFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMutableDescriptorTypeFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MutableDescriptorTypeCreateInfoEXT, DescriptorSetLayoutCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MutableDescriptorTypeCreateInfoEXT, DescriptorPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_legacy_vertex_attributes ===
  template <>
  struct StructExtends<PhysicalDeviceLegacyVertexAttributesFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceLegacyVertexAttributesFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceLegacyVertexAttributesPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_layer_settings ===
  template <>
  struct StructExtends<LayerSettingsCreateInfoEXT, InstanceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_shader_core_builtins ===
  template <>
  struct StructExtends<PhysicalDeviceShaderCoreBuiltinsFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderCoreBuiltinsFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderCoreBuiltinsPropertiesARM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_pipeline_library_group_handles ===
  template <>
  struct StructExtends<PhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineLibraryGroupHandlesFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_dynamic_rendering_unused_attachments ===
  template <>
  struct StructExtends<PhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDynamicRenderingUnusedAttachmentsFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_internally_synchronized_queues ===
  template <>
  struct StructExtends<PhysicalDeviceInternallySynchronizedQueuesFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceInternallySynchronizedQueuesFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_low_latency2 ===
  template <>
  struct StructExtends<LatencySubmissionPresentIdNV, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<LatencySubmissionPresentIdNV, SubmitInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SwapchainLatencyCreateInfoNV, SwapchainCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<LatencySurfaceCapabilitiesNV, SurfaceCapabilities2KHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_cooperative_matrix ===
  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrixFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrixFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrixPropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_data_graph ===
  template <>
  struct StructExtends<PhysicalDeviceDataGraphFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDataGraphFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphPipelineCompilerControlCreateInfoARM, DataGraphPipelineCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphPipelineShaderModuleCreateInfoARM, DataGraphPipelineCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphPipelineIdentifierCreateInfoARM, DataGraphPipelineCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphProcessingEngineCreateInfoARM, DataGraphPipelineCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphProcessingEngineCreateInfoARM, DescriptorPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphProcessingEngineCreateInfoARM, CommandPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphPipelineConstantTensorSemiStructuredSparsityInfoARM, DataGraphPipelineConstantARM>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_multiview_per_view_render_areas ===
  template <>
  struct StructExtends<PhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMultiviewPerViewRenderAreasFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MultiviewPerViewRenderAreasRenderPassBeginInfoQCOM, RenderPassBeginInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MultiviewPerViewRenderAreasRenderPassBeginInfoQCOM, RenderingInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_compute_shader_derivatives ===
  template <>
  struct StructExtends<PhysicalDeviceComputeShaderDerivativesFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceComputeShaderDerivativesFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceComputeShaderDerivativesPropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_decode_av1 ===
  template <>
  struct StructExtends<VideoDecodeAV1ProfileInfoKHR, VideoProfileInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeAV1ProfileInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeAV1CapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeAV1SessionParametersCreateInfoKHR, VideoSessionParametersCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeAV1PictureInfoKHR, VideoDecodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeAV1DpbSlotInfoKHR, VideoReferenceSlotInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_encode_av1 ===
  template <>
  struct StructExtends<PhysicalDeviceVideoEncodeAV1FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVideoEncodeAV1FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1CapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1QualityLevelPropertiesKHR, VideoEncodeQualityLevelPropertiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1SessionCreateInfoKHR, VideoSessionCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1SessionParametersCreateInfoKHR, VideoSessionParametersCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1PictureInfoKHR, VideoEncodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1DpbSlotInfoKHR, VideoReferenceSlotInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1ProfileInfoKHR, VideoProfileInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1ProfileInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1GopRemainingFrameInfoKHR, VideoBeginCodingInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1RateControlInfoKHR, VideoCodingControlInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1RateControlInfoKHR, VideoBeginCodingInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1RateControlLayerInfoKHR, VideoEncodeRateControlLayerInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_decode_vp9 ===
  template <>
  struct StructExtends<PhysicalDeviceVideoDecodeVP9FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVideoDecodeVP9FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeVP9ProfileInfoKHR, VideoProfileInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeVP9ProfileInfoKHR, QueryPoolCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeVP9CapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeVP9PictureInfoKHR, VideoDecodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_maintenance1 ===
  template <>
  struct StructExtends<PhysicalDeviceVideoMaintenance1FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVideoMaintenance1FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoInlineQueryInfoKHR, VideoDecodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoInlineQueryInfoKHR, VideoEncodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_per_stage_descriptor_set ===
  template <>
  struct StructExtends<PhysicalDevicePerStageDescriptorSetFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePerStageDescriptorSetFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_image_processing2 ===
  template <>
  struct StructExtends<PhysicalDeviceImageProcessing2FeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageProcessing2FeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageProcessing2PropertiesQCOM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SamplerBlockMatchWindowCreateInfoQCOM, SamplerCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_filter_cubic_weights ===
  template <>
  struct StructExtends<PhysicalDeviceCubicWeightsFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCubicWeightsFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SamplerCubicWeightsCreateInfoQCOM, SamplerCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<BlitImageCubicWeightsInfoQCOM, BlitImageInfo2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_ycbcr_degamma ===
  template <>
  struct StructExtends<PhysicalDeviceYcbcrDegammaFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceYcbcrDegammaFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<SamplerYcbcrConversionYcbcrDegammaCreateInfoQCOM, SamplerYcbcrConversionCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_filter_cubic_clamp ===
  template <>
  struct StructExtends<PhysicalDeviceCubicClampFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCubicClampFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_attachment_feedback_loop_dynamic_state ===
  template <>
  struct StructExtends<PhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceAttachmentFeedbackLoopDynamicStateFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_unified_image_layouts ===
  template <>
  struct StructExtends<PhysicalDeviceUnifiedImageLayoutsFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceUnifiedImageLayoutsFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AttachmentFeedbackLoopInfoEXT, RenderingAttachmentInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_SCREEN_QNX )
  //=== VK_QNX_external_memory_screen_buffer ===
  template <>
  struct StructExtends<ScreenBufferFormatPropertiesQNX, ScreenBufferPropertiesQNX>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImportScreenBufferInfoQNX, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatQNX, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ExternalFormatQNX, SamplerYcbcrConversionCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExternalMemoryScreenBufferFeaturesQNX, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExternalMemoryScreenBufferFeaturesQNX, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_SCREEN_QNX*/

  //=== VK_MSFT_layered_driver ===
  template <>
  struct StructExtends<PhysicalDeviceLayeredDriverPropertiesMSFT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_descriptor_pool_overallocation ===
  template <>
  struct StructExtends<PhysicalDeviceDescriptorPoolOverallocationFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDescriptorPoolOverallocationFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_tile_memory_heap ===
  template <>
  struct StructExtends<PhysicalDeviceTileMemoryHeapFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTileMemoryHeapFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceTileMemoryHeapPropertiesQCOM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TileMemoryRequirementsQCOM, MemoryRequirements2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TileMemoryBindInfoQCOM, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TileMemorySizeInfoQCOM, RenderPassCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TileMemorySizeInfoQCOM, RenderPassCreateInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<TileMemorySizeInfoQCOM, RenderingInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_copy_memory_indirect ===
  template <>
  struct StructExtends<PhysicalDeviceCopyMemoryIndirectFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCopyMemoryIndirectFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCopyMemoryIndirectPropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_memory_decompression ===
  template <>
  struct StructExtends<PhysicalDeviceMemoryDecompressionFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMemoryDecompressionFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMemoryDecompressionPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_display_stereo ===
  template <>
  struct StructExtends<DisplaySurfaceStereoCreateInfoNV, DisplaySurfaceCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DisplayModeStereoPropertiesNV, DisplayModeProperties2KHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_encode_intra_refresh ===
  template <>
  struct StructExtends<VideoEncodeIntraRefreshCapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeSessionIntraRefreshCreateInfoKHR, VideoSessionCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeIntraRefreshInfoKHR, VideoEncodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoReferenceIntraRefreshInfoKHR, VideoReferenceSlotInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVideoEncodeIntraRefreshFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVideoEncodeIntraRefreshFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_encode_quantization_map ===
  template <>
  struct StructExtends<VideoEncodeQuantizationMapCapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoFormatQuantizationMapPropertiesKHR, VideoFormatPropertiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeQuantizationMapInfoKHR, VideoEncodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeQuantizationMapSessionParametersCreateInfoKHR, VideoSessionParametersCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVideoEncodeQuantizationMapFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVideoEncodeQuantizationMapFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH264QuantizationMapCapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeH265QuantizationMapCapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoFormatH265QuantizationMapPropertiesKHR, VideoFormatPropertiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoEncodeAV1QuantizationMapCapabilitiesKHR, VideoCapabilitiesKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoFormatAV1QuantizationMapPropertiesKHR, VideoFormatPropertiesKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_raw_access_chains ===
  template <>
  struct StructExtends<PhysicalDeviceRawAccessChainsFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRawAccessChainsFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_external_compute_queue ===
  template <>
  struct StructExtends<ExternalComputeQueueDeviceCreateInfoNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceExternalComputeQueuePropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shader_relaxed_extended_instruction ===
  template <>
  struct StructExtends<PhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderRelaxedExtendedInstructionFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_command_buffer_inheritance ===
  template <>
  struct StructExtends<PhysicalDeviceCommandBufferInheritanceFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCommandBufferInheritanceFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_maintenance7 ===
  template <>
  struct StructExtends<PhysicalDeviceMaintenance7FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance7FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance7PropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceLayeredApiPropertiesListKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceLayeredApiVulkanPropertiesKHR, PhysicalDeviceLayeredApiPropertiesKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_shader_atomic_float16_vector ===
  template <>
  struct StructExtends<PhysicalDeviceShaderAtomicFloat16VectorFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderAtomicFloat16VectorFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_replicated_composites ===
  template <>
  struct StructExtends<PhysicalDeviceShaderReplicatedCompositesFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderReplicatedCompositesFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_float8 ===
  template <>
  struct StructExtends<PhysicalDeviceShaderFloat8FeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderFloat8FeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_ray_tracing_validation ===
  template <>
  struct StructExtends<PhysicalDeviceRayTracingValidationFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingValidationFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_cluster_acceleration_structure ===
  template <>
  struct StructExtends<PhysicalDeviceClusterAccelerationStructureFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceClusterAccelerationStructureFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceClusterAccelerationStructurePropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RayTracingPipelineClusterAccelerationStructureCreateInfoNV, RayTracingPipelineCreateInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_partitioned_acceleration_structure ===
  template <>
  struct StructExtends<PhysicalDevicePartitionedAccelerationStructureFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePartitionedAccelerationStructureFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePartitionedAccelerationStructurePropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PartitionedAccelerationStructureFlagsNV, PartitionedAccelerationStructureInstancesInputNV>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<WriteDescriptorSetPartitionedAccelerationStructureNV, WriteDescriptorSet>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_device_generated_commands ===
  template <>
  struct StructExtends<PhysicalDeviceDeviceGeneratedCommandsFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDeviceGeneratedCommandsFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDeviceGeneratedCommandsPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<GeneratedCommandsPipelineInfoEXT, GeneratedCommandsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<GeneratedCommandsPipelineInfoEXT, GeneratedCommandsMemoryRequirementsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<GeneratedCommandsShaderInfoEXT, GeneratedCommandsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<GeneratedCommandsShaderInfoEXT, GeneratedCommandsMemoryRequirementsInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_device_fault ===
  template <>
  struct StructExtends<PhysicalDeviceFaultFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFaultFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFaultPropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_maintenance8 ===
  template <>
  struct StructExtends<MemoryBarrierAccessFlags3KHR, SubpassDependency2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MemoryBarrierAccessFlags3KHR, BufferMemoryBarrier2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MemoryBarrierAccessFlags3KHR, ImageMemoryBarrier2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<MemoryBarrierAccessFlags3KHR, MemoryRangeBarriersInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance8FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance8FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_MESA_image_alignment_control ===
  template <>
  struct StructExtends<PhysicalDeviceImageAlignmentControlFeaturesMESA, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageAlignmentControlFeaturesMESA, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceImageAlignmentControlPropertiesMESA, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ImageAlignmentControlCreateInfoMESA, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_shader_fma ===
  template <>
  struct StructExtends<PhysicalDeviceShaderFmaFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderFmaFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_push_constant_bank ===
  template <>
  struct StructExtends<PushConstantBankInfoNV, DescriptorSetAndBindingMappingEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PushConstantBankInfoNV, PushDataInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PushConstantBankInfoNV, PushConstantsInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PushConstantBankInfoNV, IndirectCommandsLayoutTokenEXT>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePushConstantBankFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePushConstantBankFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePushConstantBankPropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_ray_tracing_invocation_reorder ===
  template <>
  struct StructExtends<PhysicalDeviceRayTracingInvocationReorderPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingInvocationReorderFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRayTracingInvocationReorderFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_depth_clamp_control ===
  template <>
  struct StructExtends<PhysicalDeviceDepthClampControlFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDepthClampControlFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineViewportDepthClampControlCreateInfoEXT, PipelineViewportStateCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_maintenance9 ===
  template <>
  struct StructExtends<PhysicalDeviceMaintenance9FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance9FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance9PropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<QueueFamilyOwnershipTransferPropertiesKHR, QueueFamilyProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_video_maintenance2 ===
  template <>
  struct StructExtends<PhysicalDeviceVideoMaintenance2FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVideoMaintenance2FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH264InlineSessionParametersInfoKHR, VideoDecodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeH265InlineSessionParametersInfoKHR, VideoDecodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<VideoDecodeAV1InlineSessionParametersInfoKHR, VideoDecodeInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_HUAWEI_hdr_vivid ===
  template <>
  struct StructExtends<PhysicalDeviceHdrVividFeaturesHUAWEI, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceHdrVividFeaturesHUAWEI, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<HdrVividDynamicMetadataHUAWEI, HdrMetadataEXT>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_cooperative_matrix2 ===
  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrix2FeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrix2FeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCooperativeMatrix2PropertiesNV, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_pipeline_opacity_micromap ===
  template <>
  struct StructExtends<PhysicalDevicePipelineOpacityMicromapFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineOpacityMicromapFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

#  if defined( VK_USE_PLATFORM_METAL_EXT )
  //=== VK_EXT_external_memory_metal ===
  template <>
  struct StructExtends<ImportMemoryMetalHandleInfoEXT, MemoryAllocateInfo>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_USE_PLATFORM_METAL_EXT*/

  //=== VK_KHR_depth_clamp_zero_one ===
  template <>
  struct StructExtends<PhysicalDeviceDepthClampZeroOneFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDepthClampZeroOneFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_performance_counters_by_region ===
  template <>
  struct StructExtends<PhysicalDevicePerformanceCountersByRegionFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePerformanceCountersByRegionFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePerformanceCountersByRegionPropertiesARM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassPerformanceCountersByRegionBeginInfoARM, RenderPassBeginInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassPerformanceCountersByRegionBeginInfoARM, RenderingInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_shader_instrumentation ===
  template <>
  struct StructExtends<PhysicalDeviceShaderInstrumentationFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderInstrumentationFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderInstrumentationPropertiesARM, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_vertex_attribute_robustness ===
  template <>
  struct StructExtends<PhysicalDeviceVertexAttributeRobustnessFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceVertexAttributeRobustnessFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_format_pack ===
  template <>
  struct StructExtends<PhysicalDeviceFormatPackFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFormatPackFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_VALVE_fragment_density_map_layered ===
  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMapLayeredFeaturesVALVE, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMapLayeredFeaturesVALVE, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMapLayeredPropertiesVALVE, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PipelineFragmentDensityMapLayeredCreateInfoVALVE, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_robustness2 ===
  template <>
  struct StructExtends<PhysicalDeviceRobustness2FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRobustness2FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceRobustness2PropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_present_metering ===
  template <>
  struct StructExtends<SetPresentConfigNV, PresentInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentMeteringFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentMeteringFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_fragment_density_map_offset ===
  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMapOffsetFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMapOffsetFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceFragmentDensityMapOffsetPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassFragmentDensityMapOffsetEndInfoEXT, SubpassEndInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderPassFragmentDensityMapOffsetEndInfoEXT, RenderingEndInfoKHR>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_zero_initialize_device_memory ===
  template <>
  struct StructExtends<PhysicalDeviceZeroInitializeDeviceMemoryFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceZeroInitializeDeviceMemoryFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_present_mode_fifo_latest_ready ===
  template <>
  struct StructExtends<PhysicalDevicePresentModeFifoLatestReadyFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePresentModeFifoLatestReadyFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_opacity_micromap ===
  template <>
  struct StructExtends<AccelerationStructureGeometryMicromapDataKHR, AccelerationStructureGeometryKHR>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceOpacityMicromapFeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceOpacityMicromapFeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceOpacityMicromapPropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<AccelerationStructureTrianglesOpacityMicromapKHR, AccelerationStructureGeometryTrianglesDataKHR>
  {
    enum
    {
      value = true
    };
  };
#  if defined( VK_ENABLE_BETA_EXTENSIONS )
  template <>
  struct StructExtends<AccelerationStructureTrianglesOpacityMicromapKHR, AccelerationStructureDenseGeometryFormatTrianglesDataAMDX>
  {
    enum
    {
      value = true
    };
  };
#  endif /*VK_ENABLE_BETA_EXTENSIONS*/

  //=== VK_EXT_shader_64bit_indexing ===
  template <>
  struct StructExtends<PhysicalDeviceShader64BitIndexingFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShader64BitIndexingFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_custom_resolve ===
  template <>
  struct StructExtends<PhysicalDeviceCustomResolveFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceCustomResolveFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<CustomResolveCreateInfoEXT, GraphicsPipelineCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<CustomResolveCreateInfoEXT, CommandBufferInheritanceInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<CustomResolveCreateInfoEXT, ShaderCreateInfoEXT>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_QCOM_data_graph_model ===
  template <>
  struct StructExtends<DataGraphPipelineBuiltinModelCreateInfoQCOM, DataGraphPipelineCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDataGraphModelFeaturesQCOM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDataGraphModelFeaturesQCOM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_maintenance10 ===
  template <>
  struct StructExtends<PhysicalDeviceMaintenance10FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance10FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance10PropertiesKHR, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<RenderingAttachmentFlagsInfoKHR, RenderingAttachmentInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<ResolveImageModeInfoKHR, ResolveImageInfo2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_data_graph_optical_flow ===
  template <>
  struct StructExtends<PhysicalDeviceDataGraphOpticalFlowFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDataGraphOpticalFlowFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphPipelineOpticalFlowCreateInfoARM, DataGraphPipelineCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphOpticalFlowImageFormatInfoARM, PhysicalDeviceImageFormatInfo2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphOpticalFlowImageFormatInfoARM, ImageCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphPipelineOpticalFlowDispatchInfoARM, DataGraphPipelineDispatchInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphPipelineResourceInfoImageLayoutARM, DataGraphPipelineResourceInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphPipelineSingleNodeCreateInfoARM, DataGraphPipelineCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_long_vector ===
  template <>
  struct StructExtends<PhysicalDeviceShaderLongVectorFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderLongVectorFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderLongVectorPropertiesEXT, PhysicalDeviceProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_SEC_pipeline_cache_incremental_mode ===
  template <>
  struct StructExtends<PhysicalDevicePipelineCacheIncrementalModeFeaturesSEC, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePipelineCacheIncrementalModeFeaturesSEC, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_uniform_buffer_unsized_array ===
  template <>
  struct StructExtends<PhysicalDeviceShaderUniformBufferUnsizedArrayFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderUniformBufferUnsizedArrayFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_NV_compute_occupancy_priority ===
  template <>
  struct StructExtends<PhysicalDeviceComputeOccupancyPriorityFeaturesNV, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceComputeOccupancyPriorityFeaturesNV, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_KHR_maintenance11 ===
  template <>
  struct StructExtends<PhysicalDeviceMaintenance11FeaturesKHR, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceMaintenance11FeaturesKHR, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<QueueFamilyOptimalImageTransferGranularityPropertiesKHR, QueueFamilyProperties2>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_shader_subgroup_partitioned ===
  template <>
  struct StructExtends<PhysicalDeviceShaderSubgroupPartitionedFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderSubgroupPartitionedFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_VALVE_shader_mixed_float_dot_product ===
  template <>
  struct StructExtends<PhysicalDeviceShaderMixedFloatDotProductFeaturesVALVE, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceShaderMixedFloatDotProductFeaturesVALVE, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_SEC_throttle_hint ===
  template <>
  struct StructExtends<ThrottleHintSubmitInfoSEC, SubmitInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceThrottleHintFeaturesSEC, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceThrottleHintFeaturesSEC, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_ARM_data_graph_neural_accelerator_statistics ===
  template <>
  struct StructExtends<PhysicalDeviceDataGraphNeuralAcceleratorStatisticsFeaturesARM, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDeviceDataGraphNeuralAcceleratorStatisticsFeaturesARM, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphPipelineNeuralStatisticsCreateInfoARM, DataGraphPipelineCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<DataGraphPipelineSessionNeuralStatisticsCreateInfoARM, DataGraphPipelineSessionCreateInfoARM>
  {
    enum
    {
      value = true
    };
  };

  //=== VK_EXT_primitive_restart_index ===
  template <>
  struct StructExtends<PhysicalDevicePrimitiveRestartIndexFeaturesEXT, PhysicalDeviceFeatures2>
  {
    enum
    {
      value = true
    };
  };

  template <>
  struct StructExtends<PhysicalDevicePrimitiveRestartIndexFeaturesEXT, DeviceCreateInfo>
  {
    enum
    {
      value = true
    };
  };

#endif  // VULKAN_HPP_DISABLE_ENHANCED_MODE

  namespace detail
  {
#if VULKAN_HPP_ENABLE_DYNAMIC_LOADER_TOOL
    class DynamicLoader
    {
    public:
#  ifdef VULKAN_HPP_NO_EXCEPTIONS
      DynamicLoader( std::string const & vulkanLibraryName = {} ) VULKAN_HPP_NOEXCEPT
#  else
      DynamicLoader( std::string const & vulkanLibraryName = {} )
#  endif
      {
        if ( !vulkanLibraryName.empty() )
        {
#  if defined( _WIN32 )
          m_library = ::LoadLibraryA( vulkanLibraryName.c_str() );
#  elif defined( __unix__ ) || defined( __APPLE__ ) || defined( __QNX__ ) || defined( __Fuchsia__ )
          m_library = dlopen( vulkanLibraryName.c_str(), RTLD_NOW | RTLD_LOCAL );
#  else
#    error unsupported platform
#  endif
        }
        else
        {
#  if defined( _WIN32 )
          m_library = ::LoadLibraryA( "vulkan-1.dll" );
#  elif defined( __APPLE__ )
          m_library = dlopen( "libvulkan.dylib", RTLD_NOW | RTLD_LOCAL );
          if ( !m_library )
          {
            m_library = dlopen( "libvulkan.1.dylib", RTLD_NOW | RTLD_LOCAL );
          }
          // modern versions of macOS don't search /usr/local/lib automatically contrary to what man dlopen says
          // Vulkan SDK uses this as the system-wide installation location, so we're going to fallback to this if all else fails
          if ( !m_library && ( std::getenv( "DYLD_FALLBACK_LIBRARY_PATH" ) == NULL ) )
          {
            m_library = dlopen( "/usr/local/lib/libvulkan.dylib", RTLD_NOW | RTLD_LOCAL );
          }
          // for Homebrew installations on Apple Silicon
          if ( !m_library )
          {
            m_library = dlopen( "/opt/homebrew/lib/libvulkan.dylib", RTLD_NOW | RTLD_LOCAL );
          }
          if ( !m_library )
          {
            m_library = dlopen( "libMoltenVK.dylib", RTLD_NOW | RTLD_LOCAL );
          }
          // Add support for using Vulkan and MoltenVK in a Framework. App store rules for iOS
          // strictly enforce no .dylib's. If they aren't found it just falls through
          if ( !m_library )
          {
            m_library = dlopen( "vulkan.framework/vulkan", RTLD_NOW | RTLD_LOCAL );
          }
          if ( !m_library )
          {
            m_library = dlopen( "MoltenVK.framework/MoltenVK", RTLD_NOW | RTLD_LOCAL );
          }
#  elif defined( __unix__ ) || defined( __QNX__ ) || defined( __Fuchsia__ )
          m_library = dlopen( "libvulkan.so", RTLD_NOW | RTLD_LOCAL );
          if ( !m_library )
          {
            m_library = dlopen( "libvulkan.so.1", RTLD_NOW | RTLD_LOCAL );
          }
#  else
#    error unsupported platform
#  endif
        }

#  ifndef VULKAN_HPP_NO_EXCEPTIONS
        if ( !m_library )
        {
          // NOTE there should be an InitializationFailedError, but msvc insists on the symbol does not exist within the scope of this function.
          throw std::runtime_error( "Failed to load vulkan library!" );
        }
#  endif
      }

      DynamicLoader( DynamicLoader const & ) = delete;

      DynamicLoader( DynamicLoader && other ) VULKAN_HPP_NOEXCEPT : m_library( other.m_library )
      {
        other.m_library = nullptr;
      }

      DynamicLoader & operator=( DynamicLoader const & ) = delete;

      DynamicLoader & operator=( DynamicLoader && other ) VULKAN_HPP_NOEXCEPT
      {
        std::swap( m_library, other.m_library );
        return *this;
      }

      ~DynamicLoader() VULKAN_HPP_NOEXCEPT
      {
        if ( m_library )
        {
#  if defined( __unix__ ) || defined( __APPLE__ ) || defined( __QNX__ ) || defined( __Fuchsia__ )
          dlclose( m_library );
#  elif defined( _WIN32 )
          ::FreeLibrary( m_library );
#  else
#    error unsupported platform
#  endif
        }
      }

      template <typename T>
      T getProcAddress( char const * function ) const VULKAN_HPP_NOEXCEPT
      {
#  if defined( __unix__ ) || defined( __APPLE__ ) || defined( __QNX__ ) || defined( __Fuchsia__ )
        return (T)(void *)dlsym( m_library, function );
#  elif defined( _WIN32 )
        return (T)(void *)::GetProcAddress( m_library, function );
#  else
#    error unsupported platform
#  endif
      }

      bool success() const VULKAN_HPP_NOEXCEPT
      {
        return m_library != nullptr;
      }

    private:
#  if defined( __unix__ ) || defined( __APPLE__ ) || defined( __QNX__ ) || defined( __Fuchsia__ )
      void * m_library;
#  elif defined( _WIN32 )
      ::HINSTANCE m_library;
#  else
#    error unsupported platform
#  endif
    };
#endif

    using PFN_dummy = void ( * )();

    class DispatchLoaderDynamic : public DispatchLoaderBase
    {
    public:
      //=== VK_VERSION_1_0 ===
      PFN_vkCreateInstance                               vkCreateInstance                               = 0;
      PFN_vkDestroyInstance                              vkDestroyInstance                              = 0;
      PFN_vkEnumeratePhysicalDevices                     vkEnumeratePhysicalDevices                     = 0;
      PFN_vkGetPhysicalDeviceFeatures                    vkGetPhysicalDeviceFeatures                    = 0;
      PFN_vkGetPhysicalDeviceFormatProperties            vkGetPhysicalDeviceFormatProperties            = 0;
      PFN_vkGetPhysicalDeviceImageFormatProperties       vkGetPhysicalDeviceImageFormatProperties       = 0;
      PFN_vkGetPhysicalDeviceProperties                  vkGetPhysicalDeviceProperties                  = 0;
      PFN_vkGetPhysicalDeviceQueueFamilyProperties       vkGetPhysicalDeviceQueueFamilyProperties       = 0;
      PFN_vkGetPhysicalDeviceMemoryProperties            vkGetPhysicalDeviceMemoryProperties            = 0;
      PFN_vkGetInstanceProcAddr                          vkGetInstanceProcAddr                          = 0;
      PFN_vkGetDeviceProcAddr                            vkGetDeviceProcAddr                            = 0;
      PFN_vkCreateDevice                                 vkCreateDevice                                 = 0;
      PFN_vkDestroyDevice                                vkDestroyDevice                                = 0;
      PFN_vkEnumerateInstanceExtensionProperties         vkEnumerateInstanceExtensionProperties         = 0;
      PFN_vkEnumerateDeviceExtensionProperties           vkEnumerateDeviceExtensionProperties           = 0;
      PFN_vkEnumerateInstanceLayerProperties             vkEnumerateInstanceLayerProperties             = 0;
      PFN_vkEnumerateDeviceLayerProperties               vkEnumerateDeviceLayerProperties               = 0;
      PFN_vkGetDeviceQueue                               vkGetDeviceQueue                               = 0;
      PFN_vkQueueSubmit                                  vkQueueSubmit                                  = 0;
      PFN_vkQueueWaitIdle                                vkQueueWaitIdle                                = 0;
      PFN_vkDeviceWaitIdle                               vkDeviceWaitIdle                               = 0;
      PFN_vkAllocateMemory                               vkAllocateMemory                               = 0;
      PFN_vkFreeMemory                                   vkFreeMemory                                   = 0;
      PFN_vkMapMemory                                    vkMapMemory                                    = 0;
      PFN_vkUnmapMemory                                  vkUnmapMemory                                  = 0;
      PFN_vkFlushMappedMemoryRanges                      vkFlushMappedMemoryRanges                      = 0;
      PFN_vkInvalidateMappedMemoryRanges                 vkInvalidateMappedMemoryRanges                 = 0;
      PFN_vkGetDeviceMemoryCommitment                    vkGetDeviceMemoryCommitment                    = 0;
      PFN_vkBindBufferMemory                             vkBindBufferMemory                             = 0;
      PFN_vkBindImageMemory                              vkBindImageMemory                              = 0;
      PFN_vkGetBufferMemoryRequirements                  vkGetBufferMemoryRequirements                  = 0;
      PFN_vkGetImageMemoryRequirements                   vkGetImageMemoryRequirements                   = 0;
      PFN_vkGetImageSparseMemoryRequirements             vkGetImageSparseMemoryRequirements             = 0;
      PFN_vkGetPhysicalDeviceSparseImageFormatProperties vkGetPhysicalDeviceSparseImageFormatProperties = 0;
      PFN_vkQueueBindSparse                              vkQueueBindSparse                              = 0;
      PFN_vkCreateFence                                  vkCreateFence                                  = 0;
      PFN_vkDestroyFence                                 vkDestroyFence                                 = 0;
      PFN_vkResetFences                                  vkResetFences                                  = 0;
      PFN_vkGetFenceStatus                               vkGetFenceStatus                               = 0;
      PFN_vkWaitForFences                                vkWaitForFences                                = 0;
      PFN_vkCreateSemaphore                              vkCreateSemaphore                              = 0;
      PFN_vkDestroySemaphore                             vkDestroySemaphore                             = 0;
      PFN_vkCreateQueryPool                              vkCreateQueryPool                              = 0;
      PFN_vkDestroyQueryPool                             vkDestroyQueryPool                             = 0;
      PFN_vkGetQueryPoolResults                          vkGetQueryPoolResults                          = 0;
      PFN_vkCreateBuffer                                 vkCreateBuffer                                 = 0;
      PFN_vkDestroyBuffer                                vkDestroyBuffer                                = 0;
      PFN_vkCreateImage                                  vkCreateImage                                  = 0;
      PFN_vkDestroyImage                                 vkDestroyImage                                 = 0;
      PFN_vkGetImageSubresourceLayout                    vkGetImageSubresourceLayout                    = 0;
      PFN_vkCreateImageView                              vkCreateImageView                              = 0;
      PFN_vkDestroyImageView                             vkDestroyImageView                             = 0;
      PFN_vkCreateCommandPool                            vkCreateCommandPool                            = 0;
      PFN_vkDestroyCommandPool                           vkDestroyCommandPool                           = 0;
      PFN_vkResetCommandPool                             vkResetCommandPool                             = 0;
      PFN_vkAllocateCommandBuffers                       vkAllocateCommandBuffers                       = 0;
      PFN_vkFreeCommandBuffers                           vkFreeCommandBuffers                           = 0;
      PFN_vkBeginCommandBuffer                           vkBeginCommandBuffer                           = 0;
      PFN_vkEndCommandBuffer                             vkEndCommandBuffer                             = 0;
      PFN_vkResetCommandBuffer                           vkResetCommandBuffer                           = 0;
      PFN_vkCmdCopyBuffer                                vkCmdCopyBuffer                                = 0;
      PFN_vkCmdCopyImage                                 vkCmdCopyImage                                 = 0;
      PFN_vkCmdCopyBufferToImage                         vkCmdCopyBufferToImage                         = 0;
      PFN_vkCmdCopyImageToBuffer                         vkCmdCopyImageToBuffer                         = 0;
      PFN_vkCmdUpdateBuffer                              vkCmdUpdateBuffer                              = 0;
      PFN_vkCmdFillBuffer                                vkCmdFillBuffer                                = 0;
      PFN_vkCmdPipelineBarrier                           vkCmdPipelineBarrier                           = 0;
      PFN_vkCmdBeginQuery                                vkCmdBeginQuery                                = 0;
      PFN_vkCmdEndQuery                                  vkCmdEndQuery                                  = 0;
      PFN_vkCmdResetQueryPool                            vkCmdResetQueryPool                            = 0;
      PFN_vkCmdWriteTimestamp                            vkCmdWriteTimestamp                            = 0;
      PFN_vkCmdCopyQueryPoolResults                      vkCmdCopyQueryPoolResults                      = 0;
      PFN_vkCmdExecuteCommands                           vkCmdExecuteCommands                           = 0;
      PFN_vkCreateEvent                                  vkCreateEvent                                  = 0;
      PFN_vkDestroyEvent                                 vkDestroyEvent                                 = 0;
      PFN_vkGetEventStatus                               vkGetEventStatus                               = 0;
      PFN_vkSetEvent                                     vkSetEvent                                     = 0;
      PFN_vkResetEvent                                   vkResetEvent                                   = 0;
      PFN_vkCreateBufferView                             vkCreateBufferView                             = 0;
      PFN_vkDestroyBufferView                            vkDestroyBufferView                            = 0;
      PFN_vkCreateShaderModule                           vkCreateShaderModule                           = 0;
      PFN_vkDestroyShaderModule                          vkDestroyShaderModule                          = 0;
      PFN_vkCreatePipelineCache                          vkCreatePipelineCache                          = 0;
      PFN_vkDestroyPipelineCache                         vkDestroyPipelineCache                         = 0;
      PFN_vkGetPipelineCacheData                         vkGetPipelineCacheData                         = 0;
      PFN_vkMergePipelineCaches                          vkMergePipelineCaches                          = 0;
      PFN_vkCreateComputePipelines                       vkCreateComputePipelines                       = 0;
      PFN_vkDestroyPipeline                              vkDestroyPipeline                              = 0;
      PFN_vkCreatePipelineLayout                         vkCreatePipelineLayout                         = 0;
      PFN_vkDestroyPipelineLayout                        vkDestroyPipelineLayout                        = 0;
      PFN_vkCreateSampler                                vkCreateSampler                                = 0;
      PFN_vkDestroySampler                               vkDestroySampler                               = 0;
      PFN_vkCreateDescriptorSetLayout                    vkCreateDescriptorSetLayout                    = 0;
      PFN_vkDestroyDescriptorSetLayout                   vkDestroyDescriptorSetLayout                   = 0;
      PFN_vkCreateDescriptorPool                         vkCreateDescriptorPool                         = 0;
      PFN_vkDestroyDescriptorPool                        vkDestroyDescriptorPool                        = 0;
      PFN_vkResetDescriptorPool                          vkResetDescriptorPool                          = 0;
      PFN_vkAllocateDescriptorSets                       vkAllocateDescriptorSets                       = 0;
      PFN_vkFreeDescriptorSets                           vkFreeDescriptorSets                           = 0;
      PFN_vkUpdateDescriptorSets                         vkUpdateDescriptorSets                         = 0;
      PFN_vkCmdBindPipeline                              vkCmdBindPipeline                              = 0;
      PFN_vkCmdBindDescriptorSets                        vkCmdBindDescriptorSets                        = 0;
      PFN_vkCmdClearColorImage                           vkCmdClearColorImage                           = 0;
      PFN_vkCmdDispatch                                  vkCmdDispatch                                  = 0;
      PFN_vkCmdDispatchIndirect                          vkCmdDispatchIndirect                          = 0;
      PFN_vkCmdSetEvent                                  vkCmdSetEvent                                  = 0;
      PFN_vkCmdResetEvent                                vkCmdResetEvent                                = 0;
      PFN_vkCmdWaitEvents                                vkCmdWaitEvents                                = 0;
      PFN_vkCmdPushConstants                             vkCmdPushConstants                             = 0;
      PFN_vkCreateGraphicsPipelines                      vkCreateGraphicsPipelines                      = 0;
      PFN_vkCreateFramebuffer                            vkCreateFramebuffer                            = 0;
      PFN_vkDestroyFramebuffer                           vkDestroyFramebuffer                           = 0;
      PFN_vkCreateRenderPass                             vkCreateRenderPass                             = 0;
      PFN_vkDestroyRenderPass                            vkDestroyRenderPass                            = 0;
      PFN_vkGetRenderAreaGranularity                     vkGetRenderAreaGranularity                     = 0;
      PFN_vkCmdSetViewport                               vkCmdSetViewport                               = 0;
      PFN_vkCmdSetScissor                                vkCmdSetScissor                                = 0;
      PFN_vkCmdSetLineWidth                              vkCmdSetLineWidth                              = 0;
      PFN_vkCmdSetDepthBias                              vkCmdSetDepthBias                              = 0;
      PFN_vkCmdSetBlendConstants                         vkCmdSetBlendConstants                         = 0;
      PFN_vkCmdSetDepthBounds                            vkCmdSetDepthBounds                            = 0;
      PFN_vkCmdSetStencilCompareMask                     vkCmdSetStencilCompareMask                     = 0;
      PFN_vkCmdSetStencilWriteMask                       vkCmdSetStencilWriteMask                       = 0;
      PFN_vkCmdSetStencilReference                       vkCmdSetStencilReference                       = 0;
      PFN_vkCmdBindIndexBuffer                           vkCmdBindIndexBuffer                           = 0;
      PFN_vkCmdBindVertexBuffers                         vkCmdBindVertexBuffers                         = 0;
      PFN_vkCmdDraw                                      vkCmdDraw                                      = 0;
      PFN_vkCmdDrawIndexed                               vkCmdDrawIndexed                               = 0;
      PFN_vkCmdDrawIndirect                              vkCmdDrawIndirect                              = 0;
      PFN_vkCmdDrawIndexedIndirect                       vkCmdDrawIndexedIndirect                       = 0;
      PFN_vkCmdBlitImage                                 vkCmdBlitImage                                 = 0;
      PFN_vkCmdClearDepthStencilImage                    vkCmdClearDepthStencilImage                    = 0;
      PFN_vkCmdClearAttachments                          vkCmdClearAttachments                          = 0;
      PFN_vkCmdResolveImage                              vkCmdResolveImage                              = 0;
      PFN_vkCmdBeginRenderPass                           vkCmdBeginRenderPass                           = 0;
      PFN_vkCmdNextSubpass                               vkCmdNextSubpass                               = 0;
      PFN_vkCmdEndRenderPass                             vkCmdEndRenderPass                             = 0;

      //=== VK_VERSION_1_1 ===
      PFN_vkEnumerateInstanceVersion                      vkEnumerateInstanceVersion                      = 0;
      PFN_vkBindBufferMemory2                             vkBindBufferMemory2                             = 0;
      PFN_vkBindImageMemory2                              vkBindImageMemory2                              = 0;
      PFN_vkGetDeviceGroupPeerMemoryFeatures              vkGetDeviceGroupPeerMemoryFeatures              = 0;
      PFN_vkCmdSetDeviceMask                              vkCmdSetDeviceMask                              = 0;
      PFN_vkEnumeratePhysicalDeviceGroups                 vkEnumeratePhysicalDeviceGroups                 = 0;
      PFN_vkGetImageMemoryRequirements2                   vkGetImageMemoryRequirements2                   = 0;
      PFN_vkGetBufferMemoryRequirements2                  vkGetBufferMemoryRequirements2                  = 0;
      PFN_vkGetImageSparseMemoryRequirements2             vkGetImageSparseMemoryRequirements2             = 0;
      PFN_vkGetPhysicalDeviceFeatures2                    vkGetPhysicalDeviceFeatures2                    = 0;
      PFN_vkGetPhysicalDeviceProperties2                  vkGetPhysicalDeviceProperties2                  = 0;
      PFN_vkGetPhysicalDeviceFormatProperties2            vkGetPhysicalDeviceFormatProperties2            = 0;
      PFN_vkGetPhysicalDeviceImageFormatProperties2       vkGetPhysicalDeviceImageFormatProperties2       = 0;
      PFN_vkGetPhysicalDeviceQueueFamilyProperties2       vkGetPhysicalDeviceQueueFamilyProperties2       = 0;
      PFN_vkGetPhysicalDeviceMemoryProperties2            vkGetPhysicalDeviceMemoryProperties2            = 0;
      PFN_vkGetPhysicalDeviceSparseImageFormatProperties2 vkGetPhysicalDeviceSparseImageFormatProperties2 = 0;
      PFN_vkTrimCommandPool                               vkTrimCommandPool                               = 0;
      PFN_vkGetDeviceQueue2                               vkGetDeviceQueue2                               = 0;
      PFN_vkGetPhysicalDeviceExternalBufferProperties     vkGetPhysicalDeviceExternalBufferProperties     = 0;
      PFN_vkGetPhysicalDeviceExternalFenceProperties      vkGetPhysicalDeviceExternalFenceProperties      = 0;
      PFN_vkGetPhysicalDeviceExternalSemaphoreProperties  vkGetPhysicalDeviceExternalSemaphoreProperties  = 0;
      PFN_vkCmdDispatchBase                               vkCmdDispatchBase                               = 0;
      PFN_vkCreateDescriptorUpdateTemplate                vkCreateDescriptorUpdateTemplate                = 0;
      PFN_vkDestroyDescriptorUpdateTemplate               vkDestroyDescriptorUpdateTemplate               = 0;
      PFN_vkUpdateDescriptorSetWithTemplate               vkUpdateDescriptorSetWithTemplate               = 0;
      PFN_vkGetDescriptorSetLayoutSupport                 vkGetDescriptorSetLayoutSupport                 = 0;
      PFN_vkCreateSamplerYcbcrConversion                  vkCreateSamplerYcbcrConversion                  = 0;
      PFN_vkDestroySamplerYcbcrConversion                 vkDestroySamplerYcbcrConversion                 = 0;

      //=== VK_VERSION_1_2 ===
      PFN_vkResetQueryPool                      vkResetQueryPool                      = 0;
      PFN_vkGetSemaphoreCounterValue            vkGetSemaphoreCounterValue            = 0;
      PFN_vkWaitSemaphores                      vkWaitSemaphores                      = 0;
      PFN_vkSignalSemaphore                     vkSignalSemaphore                     = 0;
      PFN_vkGetBufferDeviceAddress              vkGetBufferDeviceAddress              = 0;
      PFN_vkGetBufferOpaqueCaptureAddress       vkGetBufferOpaqueCaptureAddress       = 0;
      PFN_vkGetDeviceMemoryOpaqueCaptureAddress vkGetDeviceMemoryOpaqueCaptureAddress = 0;
      PFN_vkCmdDrawIndirectCount                vkCmdDrawIndirectCount                = 0;
      PFN_vkCmdDrawIndexedIndirectCount         vkCmdDrawIndexedIndirectCount         = 0;
      PFN_vkCreateRenderPass2                   vkCreateRenderPass2                   = 0;
      PFN_vkCmdBeginRenderPass2                 vkCmdBeginRenderPass2                 = 0;
      PFN_vkCmdNextSubpass2                     vkCmdNextSubpass2                     = 0;
      PFN_vkCmdEndRenderPass2                   vkCmdEndRenderPass2                   = 0;

      //=== VK_VERSION_1_3 ===
      PFN_vkGetPhysicalDeviceToolProperties        vkGetPhysicalDeviceToolProperties        = 0;
      PFN_vkCreatePrivateDataSlot                  vkCreatePrivateDataSlot                  = 0;
      PFN_vkDestroyPrivateDataSlot                 vkDestroyPrivateDataSlot                 = 0;
      PFN_vkSetPrivateData                         vkSetPrivateData                         = 0;
      PFN_vkGetPrivateData                         vkGetPrivateData                         = 0;
      PFN_vkCmdPipelineBarrier2                    vkCmdPipelineBarrier2                    = 0;
      PFN_vkCmdWriteTimestamp2                     vkCmdWriteTimestamp2                     = 0;
      PFN_vkQueueSubmit2                           vkQueueSubmit2                           = 0;
      PFN_vkCmdCopyBuffer2                         vkCmdCopyBuffer2                         = 0;
      PFN_vkCmdCopyImage2                          vkCmdCopyImage2                          = 0;
      PFN_vkCmdCopyBufferToImage2                  vkCmdCopyBufferToImage2                  = 0;
      PFN_vkCmdCopyImageToBuffer2                  vkCmdCopyImageToBuffer2                  = 0;
      PFN_vkGetDeviceBufferMemoryRequirements      vkGetDeviceBufferMemoryRequirements      = 0;
      PFN_vkGetDeviceImageMemoryRequirements       vkGetDeviceImageMemoryRequirements       = 0;
      PFN_vkGetDeviceImageSparseMemoryRequirements vkGetDeviceImageSparseMemoryRequirements = 0;
      PFN_vkCmdSetEvent2                           vkCmdSetEvent2                           = 0;
      PFN_vkCmdResetEvent2                         vkCmdResetEvent2                         = 0;
      PFN_vkCmdWaitEvents2                         vkCmdWaitEvents2                         = 0;
      PFN_vkCmdBlitImage2                          vkCmdBlitImage2                          = 0;
      PFN_vkCmdResolveImage2                       vkCmdResolveImage2                       = 0;
      PFN_vkCmdBeginRendering                      vkCmdBeginRendering                      = 0;
      PFN_vkCmdEndRendering                        vkCmdEndRendering                        = 0;
      PFN_vkCmdSetCullMode                         vkCmdSetCullMode                         = 0;
      PFN_vkCmdSetFrontFace                        vkCmdSetFrontFace                        = 0;
      PFN_vkCmdSetPrimitiveTopology                vkCmdSetPrimitiveTopology                = 0;
      PFN_vkCmdSetViewportWithCount                vkCmdSetViewportWithCount                = 0;
      PFN_vkCmdSetScissorWithCount                 vkCmdSetScissorWithCount                 = 0;
      PFN_vkCmdBindVertexBuffers2                  vkCmdBindVertexBuffers2                  = 0;
      PFN_vkCmdSetDepthTestEnable                  vkCmdSetDepthTestEnable                  = 0;
      PFN_vkCmdSetDepthWriteEnable                 vkCmdSetDepthWriteEnable                 = 0;
      PFN_vkCmdSetDepthCompareOp                   vkCmdSetDepthCompareOp                   = 0;
      PFN_vkCmdSetDepthBoundsTestEnable            vkCmdSetDepthBoundsTestEnable            = 0;
      PFN_vkCmdSetStencilTestEnable                vkCmdSetStencilTestEnable                = 0;
      PFN_vkCmdSetStencilOp                        vkCmdSetStencilOp                        = 0;
      PFN_vkCmdSetRasterizerDiscardEnable          vkCmdSetRasterizerDiscardEnable          = 0;
      PFN_vkCmdSetDepthBiasEnable                  vkCmdSetDepthBiasEnable                  = 0;
      PFN_vkCmdSetPrimitiveRestartEnable           vkCmdSetPrimitiveRestartEnable           = 0;

      //=== VK_VERSION_1_4 ===
      PFN_vkMapMemory2                            vkMapMemory2                            = 0;
      PFN_vkUnmapMemory2                          vkUnmapMemory2                          = 0;
      PFN_vkGetDeviceImageSubresourceLayout       vkGetDeviceImageSubresourceLayout       = 0;
      PFN_vkGetImageSubresourceLayout2            vkGetImageSubresourceLayout2            = 0;
      PFN_vkCopyMemoryToImage                     vkCopyMemoryToImage                     = 0;
      PFN_vkCopyImageToMemory                     vkCopyImageToMemory                     = 0;
      PFN_vkCopyImageToImage                      vkCopyImageToImage                      = 0;
      PFN_vkTransitionImageLayout                 vkTransitionImageLayout                 = 0;
      PFN_vkCmdPushDescriptorSet                  vkCmdPushDescriptorSet                  = 0;
      PFN_vkCmdPushDescriptorSetWithTemplate      vkCmdPushDescriptorSetWithTemplate      = 0;
      PFN_vkCmdBindDescriptorSets2                vkCmdBindDescriptorSets2                = 0;
      PFN_vkCmdPushConstants2                     vkCmdPushConstants2                     = 0;
      PFN_vkCmdPushDescriptorSet2                 vkCmdPushDescriptorSet2                 = 0;
      PFN_vkCmdPushDescriptorSetWithTemplate2     vkCmdPushDescriptorSetWithTemplate2     = 0;
      PFN_vkCmdSetLineStipple                     vkCmdSetLineStipple                     = 0;
      PFN_vkCmdBindIndexBuffer2                   vkCmdBindIndexBuffer2                   = 0;
      PFN_vkGetRenderingAreaGranularity           vkGetRenderingAreaGranularity           = 0;
      PFN_vkCmdSetRenderingAttachmentLocations    vkCmdSetRenderingAttachmentLocations    = 0;
      PFN_vkCmdSetRenderingInputAttachmentIndices vkCmdSetRenderingInputAttachmentIndices = 0;

      //=== VK_KHR_surface ===
      PFN_vkDestroySurfaceKHR                       vkDestroySurfaceKHR                       = 0;
      PFN_vkGetPhysicalDeviceSurfaceSupportKHR      vkGetPhysicalDeviceSurfaceSupportKHR      = 0;
      PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR vkGetPhysicalDeviceSurfaceCapabilitiesKHR = 0;
      PFN_vkGetPhysicalDeviceSurfaceFormatsKHR      vkGetPhysicalDeviceSurfaceFormatsKHR      = 0;
      PFN_vkGetPhysicalDeviceSurfacePresentModesKHR vkGetPhysicalDeviceSurfacePresentModesKHR = 0;

      //=== VK_KHR_swapchain ===
      PFN_vkCreateSwapchainKHR                    vkCreateSwapchainKHR                    = 0;
      PFN_vkDestroySwapchainKHR                   vkDestroySwapchainKHR                   = 0;
      PFN_vkGetSwapchainImagesKHR                 vkGetSwapchainImagesKHR                 = 0;
      PFN_vkAcquireNextImageKHR                   vkAcquireNextImageKHR                   = 0;
      PFN_vkQueuePresentKHR                       vkQueuePresentKHR                       = 0;
      PFN_vkGetDeviceGroupPresentCapabilitiesKHR  vkGetDeviceGroupPresentCapabilitiesKHR  = 0;
      PFN_vkGetDeviceGroupSurfacePresentModesKHR  vkGetDeviceGroupSurfacePresentModesKHR  = 0;
      PFN_vkGetPhysicalDevicePresentRectanglesKHR vkGetPhysicalDevicePresentRectanglesKHR = 0;
      PFN_vkAcquireNextImage2KHR                  vkAcquireNextImage2KHR                  = 0;

      //=== VK_KHR_display ===
      PFN_vkGetPhysicalDeviceDisplayPropertiesKHR      vkGetPhysicalDeviceDisplayPropertiesKHR      = 0;
      PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR vkGetPhysicalDeviceDisplayPlanePropertiesKHR = 0;
      PFN_vkGetDisplayPlaneSupportedDisplaysKHR        vkGetDisplayPlaneSupportedDisplaysKHR        = 0;
      PFN_vkGetDisplayModePropertiesKHR                vkGetDisplayModePropertiesKHR                = 0;
      PFN_vkCreateDisplayModeKHR                       vkCreateDisplayModeKHR                       = 0;
      PFN_vkGetDisplayPlaneCapabilitiesKHR             vkGetDisplayPlaneCapabilitiesKHR             = 0;
      PFN_vkCreateDisplayPlaneSurfaceKHR               vkCreateDisplayPlaneSurfaceKHR               = 0;

      //=== VK_KHR_display_swapchain ===
      PFN_vkCreateSharedSwapchainsKHR vkCreateSharedSwapchainsKHR = 0;

#if defined( VK_USE_PLATFORM_XLIB_KHR )
      //=== VK_KHR_xlib_surface ===
      PFN_vkCreateXlibSurfaceKHR                        vkCreateXlibSurfaceKHR                        = 0;
      PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR vkGetPhysicalDeviceXlibPresentationSupportKHR = 0;
#else
      PFN_dummy vkCreateXlibSurfaceKHR_placeholder                        = 0;
      PFN_dummy vkGetPhysicalDeviceXlibPresentationSupportKHR_placeholder = 0;
#endif /*VK_USE_PLATFORM_XLIB_KHR*/

#if defined( VK_USE_PLATFORM_XCB_KHR )
      //=== VK_KHR_xcb_surface ===
      PFN_vkCreateXcbSurfaceKHR                        vkCreateXcbSurfaceKHR                        = 0;
      PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR vkGetPhysicalDeviceXcbPresentationSupportKHR = 0;
#else
      PFN_dummy vkCreateXcbSurfaceKHR_placeholder                        = 0;
      PFN_dummy vkGetPhysicalDeviceXcbPresentationSupportKHR_placeholder = 0;
#endif /*VK_USE_PLATFORM_XCB_KHR*/

#if defined( VK_USE_PLATFORM_WAYLAND_KHR )
      //=== VK_KHR_wayland_surface ===
      PFN_vkCreateWaylandSurfaceKHR                        vkCreateWaylandSurfaceKHR                        = 0;
      PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR vkGetPhysicalDeviceWaylandPresentationSupportKHR = 0;
#else
      PFN_dummy vkCreateWaylandSurfaceKHR_placeholder                        = 0;
      PFN_dummy vkGetPhysicalDeviceWaylandPresentationSupportKHR_placeholder = 0;
#endif /*VK_USE_PLATFORM_WAYLAND_KHR*/

#if defined( VK_USE_PLATFORM_ANDROID_KHR )
      //=== VK_KHR_android_surface ===
      PFN_vkCreateAndroidSurfaceKHR vkCreateAndroidSurfaceKHR = 0;
#else
      PFN_dummy vkCreateAndroidSurfaceKHR_placeholder = 0;
#endif /*VK_USE_PLATFORM_ANDROID_KHR*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
      //=== VK_KHR_win32_surface ===
      PFN_vkCreateWin32SurfaceKHR                        vkCreateWin32SurfaceKHR                        = 0;
      PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR vkGetPhysicalDeviceWin32PresentationSupportKHR = 0;
#else
      PFN_dummy vkCreateWin32SurfaceKHR_placeholder                        = 0;
      PFN_dummy vkGetPhysicalDeviceWin32PresentationSupportKHR_placeholder = 0;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

      //=== VK_EXT_debug_report ===
      PFN_vkCreateDebugReportCallbackEXT  vkCreateDebugReportCallbackEXT  = 0;
      PFN_vkDestroyDebugReportCallbackEXT vkDestroyDebugReportCallbackEXT = 0;
      PFN_vkDebugReportMessageEXT         vkDebugReportMessageEXT         = 0;

      //=== VK_EXT_debug_marker ===
      PFN_vkDebugMarkerSetObjectTagEXT  vkDebugMarkerSetObjectTagEXT  = 0;
      PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT = 0;
      PFN_vkCmdDebugMarkerBeginEXT      vkCmdDebugMarkerBeginEXT      = 0;
      PFN_vkCmdDebugMarkerEndEXT        vkCmdDebugMarkerEndEXT        = 0;
      PFN_vkCmdDebugMarkerInsertEXT     vkCmdDebugMarkerInsertEXT     = 0;

      //=== VK_KHR_video_queue ===
      PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR     vkGetPhysicalDeviceVideoCapabilitiesKHR     = 0;
      PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR vkGetPhysicalDeviceVideoFormatPropertiesKHR = 0;
      PFN_vkCreateVideoSessionKHR                     vkCreateVideoSessionKHR                     = 0;
      PFN_vkDestroyVideoSessionKHR                    vkDestroyVideoSessionKHR                    = 0;
      PFN_vkGetVideoSessionMemoryRequirementsKHR      vkGetVideoSessionMemoryRequirementsKHR      = 0;
      PFN_vkBindVideoSessionMemoryKHR                 vkBindVideoSessionMemoryKHR                 = 0;
      PFN_vkCreateVideoSessionParametersKHR           vkCreateVideoSessionParametersKHR           = 0;
      PFN_vkUpdateVideoSessionParametersKHR           vkUpdateVideoSessionParametersKHR           = 0;
      PFN_vkDestroyVideoSessionParametersKHR          vkDestroyVideoSessionParametersKHR          = 0;
      PFN_vkCmdBeginVideoCodingKHR                    vkCmdBeginVideoCodingKHR                    = 0;
      PFN_vkCmdEndVideoCodingKHR                      vkCmdEndVideoCodingKHR                      = 0;
      PFN_vkCmdControlVideoCodingKHR                  vkCmdControlVideoCodingKHR                  = 0;

      //=== VK_KHR_video_decode_queue ===
      PFN_vkCmdDecodeVideoKHR vkCmdDecodeVideoKHR = 0;

      //=== VK_EXT_transform_feedback ===
      PFN_vkCmdBindTransformFeedbackBuffersEXT vkCmdBindTransformFeedbackBuffersEXT = 0;
      PFN_vkCmdBeginTransformFeedbackEXT       vkCmdBeginTransformFeedbackEXT       = 0;
      PFN_vkCmdEndTransformFeedbackEXT         vkCmdEndTransformFeedbackEXT         = 0;
      PFN_vkCmdBeginQueryIndexedEXT            vkCmdBeginQueryIndexedEXT            = 0;
      PFN_vkCmdEndQueryIndexedEXT              vkCmdEndQueryIndexedEXT              = 0;
      PFN_vkCmdDrawIndirectByteCountEXT        vkCmdDrawIndirectByteCountEXT        = 0;

      //=== VK_NVX_binary_import ===
      PFN_vkCreateCuModuleNVX    vkCreateCuModuleNVX    = 0;
      PFN_vkCreateCuFunctionNVX  vkCreateCuFunctionNVX  = 0;
      PFN_vkDestroyCuModuleNVX   vkDestroyCuModuleNVX   = 0;
      PFN_vkDestroyCuFunctionNVX vkDestroyCuFunctionNVX = 0;
      PFN_vkCmdCuLaunchKernelNVX vkCmdCuLaunchKernelNVX = 0;

      //=== VK_NVX_image_view_handle ===
      PFN_vkGetImageViewHandleNVX                 vkGetImageViewHandleNVX                 = 0;
      PFN_vkGetImageViewHandle64NVX               vkGetImageViewHandle64NVX               = 0;
      PFN_vkGetImageViewAddressNVX                vkGetImageViewAddressNVX                = 0;
      PFN_vkGetDeviceCombinedImageSamplerIndexNVX vkGetDeviceCombinedImageSamplerIndexNVX = 0;

      //=== VK_AMD_draw_indirect_count ===
      PFN_vkCmdDrawIndirectCountAMD        vkCmdDrawIndirectCountAMD        = 0;
      PFN_vkCmdDrawIndexedIndirectCountAMD vkCmdDrawIndexedIndirectCountAMD = 0;

      //=== VK_AMD_shader_info ===
      PFN_vkGetShaderInfoAMD vkGetShaderInfoAMD = 0;

      //=== VK_KHR_dynamic_rendering ===
      PFN_vkCmdBeginRenderingKHR vkCmdBeginRenderingKHR = 0;
      PFN_vkCmdEndRenderingKHR   vkCmdEndRenderingKHR   = 0;

#if defined( VK_USE_PLATFORM_GGP )
      //=== VK_GGP_stream_descriptor_surface ===
      PFN_vkCreateStreamDescriptorSurfaceGGP vkCreateStreamDescriptorSurfaceGGP = 0;
#else
      PFN_dummy vkCreateStreamDescriptorSurfaceGGP_placeholder = 0;
#endif /*VK_USE_PLATFORM_GGP*/

      //=== VK_NV_external_memory_capabilities ===
      PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV vkGetPhysicalDeviceExternalImageFormatPropertiesNV = 0;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
      //=== VK_NV_external_memory_win32 ===
      PFN_vkGetMemoryWin32HandleNV vkGetMemoryWin32HandleNV = 0;
#else
      PFN_dummy vkGetMemoryWin32HandleNV_placeholder = 0;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

      //=== VK_KHR_get_physical_device_properties2 ===
      PFN_vkGetPhysicalDeviceFeatures2KHR                    vkGetPhysicalDeviceFeatures2KHR                    = 0;
      PFN_vkGetPhysicalDeviceProperties2KHR                  vkGetPhysicalDeviceProperties2KHR                  = 0;
      PFN_vkGetPhysicalDeviceFormatProperties2KHR            vkGetPhysicalDeviceFormatProperties2KHR            = 0;
      PFN_vkGetPhysicalDeviceImageFormatProperties2KHR       vkGetPhysicalDeviceImageFormatProperties2KHR       = 0;
      PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR       vkGetPhysicalDeviceQueueFamilyProperties2KHR       = 0;
      PFN_vkGetPhysicalDeviceMemoryProperties2KHR            vkGetPhysicalDeviceMemoryProperties2KHR            = 0;
      PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR vkGetPhysicalDeviceSparseImageFormatProperties2KHR = 0;

      //=== VK_KHR_device_group ===
      PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR vkGetDeviceGroupPeerMemoryFeaturesKHR = 0;
      PFN_vkCmdSetDeviceMaskKHR                 vkCmdSetDeviceMaskKHR                 = 0;
      PFN_vkCmdDispatchBaseKHR                  vkCmdDispatchBaseKHR                  = 0;

#if defined( VK_USE_PLATFORM_VI_NN )
      //=== VK_NN_vi_surface ===
      PFN_vkCreateViSurfaceNN vkCreateViSurfaceNN = 0;
#else
      PFN_dummy vkCreateViSurfaceNN_placeholder = 0;
#endif /*VK_USE_PLATFORM_VI_NN*/

      //=== VK_KHR_maintenance1 ===
      PFN_vkTrimCommandPoolKHR vkTrimCommandPoolKHR = 0;

      //=== VK_KHR_device_group_creation ===
      PFN_vkEnumeratePhysicalDeviceGroupsKHR vkEnumeratePhysicalDeviceGroupsKHR = 0;

      //=== VK_KHR_external_memory_capabilities ===
      PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR vkGetPhysicalDeviceExternalBufferPropertiesKHR = 0;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
      //=== VK_KHR_external_memory_win32 ===
      PFN_vkGetMemoryWin32HandleKHR           vkGetMemoryWin32HandleKHR           = 0;
      PFN_vkGetMemoryWin32HandlePropertiesKHR vkGetMemoryWin32HandlePropertiesKHR = 0;
#else
      PFN_dummy vkGetMemoryWin32HandleKHR_placeholder           = 0;
      PFN_dummy vkGetMemoryWin32HandlePropertiesKHR_placeholder = 0;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

      //=== VK_KHR_external_memory_fd ===
      PFN_vkGetMemoryFdKHR           vkGetMemoryFdKHR           = 0;
      PFN_vkGetMemoryFdPropertiesKHR vkGetMemoryFdPropertiesKHR = 0;

      //=== VK_KHR_external_semaphore_capabilities ===
      PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR vkGetPhysicalDeviceExternalSemaphorePropertiesKHR = 0;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
      //=== VK_KHR_external_semaphore_win32 ===
      PFN_vkImportSemaphoreWin32HandleKHR vkImportSemaphoreWin32HandleKHR = 0;
      PFN_vkGetSemaphoreWin32HandleKHR    vkGetSemaphoreWin32HandleKHR    = 0;
#else
      PFN_dummy vkImportSemaphoreWin32HandleKHR_placeholder = 0;
      PFN_dummy vkGetSemaphoreWin32HandleKHR_placeholder    = 0;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

      //=== VK_KHR_external_semaphore_fd ===
      PFN_vkImportSemaphoreFdKHR vkImportSemaphoreFdKHR = 0;
      PFN_vkGetSemaphoreFdKHR    vkGetSemaphoreFdKHR    = 0;

      //=== VK_KHR_push_descriptor ===
      PFN_vkCmdPushDescriptorSetKHR             vkCmdPushDescriptorSetKHR             = 0;
      PFN_vkCmdPushDescriptorSetWithTemplateKHR vkCmdPushDescriptorSetWithTemplateKHR = 0;

      //=== VK_EXT_conditional_rendering ===
      PFN_vkCmdBeginConditionalRenderingEXT vkCmdBeginConditionalRenderingEXT = 0;
      PFN_vkCmdEndConditionalRenderingEXT   vkCmdEndConditionalRenderingEXT   = 0;

      //=== VK_KHR_descriptor_update_template ===
      PFN_vkCreateDescriptorUpdateTemplateKHR  vkCreateDescriptorUpdateTemplateKHR  = 0;
      PFN_vkDestroyDescriptorUpdateTemplateKHR vkDestroyDescriptorUpdateTemplateKHR = 0;
      PFN_vkUpdateDescriptorSetWithTemplateKHR vkUpdateDescriptorSetWithTemplateKHR = 0;

      //=== VK_NV_clip_space_w_scaling ===
      PFN_vkCmdSetViewportWScalingNV vkCmdSetViewportWScalingNV = 0;

      //=== VK_EXT_direct_mode_display ===
      PFN_vkReleaseDisplayEXT vkReleaseDisplayEXT = 0;

#if defined( VK_USE_PLATFORM_XLIB_XRANDR_EXT )
      //=== VK_EXT_acquire_xlib_display ===
      PFN_vkAcquireXlibDisplayEXT    vkAcquireXlibDisplayEXT    = 0;
      PFN_vkGetRandROutputDisplayEXT vkGetRandROutputDisplayEXT = 0;
#else
      PFN_dummy vkAcquireXlibDisplayEXT_placeholder    = 0;
      PFN_dummy vkGetRandROutputDisplayEXT_placeholder = 0;
#endif /*VK_USE_PLATFORM_XLIB_XRANDR_EXT*/

      //=== VK_EXT_display_surface_counter ===
      PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT vkGetPhysicalDeviceSurfaceCapabilities2EXT = 0;

      //=== VK_EXT_display_control ===
      PFN_vkDisplayPowerControlEXT  vkDisplayPowerControlEXT  = 0;
      PFN_vkRegisterDeviceEventEXT  vkRegisterDeviceEventEXT  = 0;
      PFN_vkRegisterDisplayEventEXT vkRegisterDisplayEventEXT = 0;
      PFN_vkGetSwapchainCounterEXT  vkGetSwapchainCounterEXT  = 0;

      //=== VK_GOOGLE_display_timing ===
      PFN_vkGetRefreshCycleDurationGOOGLE   vkGetRefreshCycleDurationGOOGLE   = 0;
      PFN_vkGetPastPresentationTimingGOOGLE vkGetPastPresentationTimingGOOGLE = 0;

      //=== VK_EXT_discard_rectangles ===
      PFN_vkCmdSetDiscardRectangleEXT       vkCmdSetDiscardRectangleEXT       = 0;
      PFN_vkCmdSetDiscardRectangleEnableEXT vkCmdSetDiscardRectangleEnableEXT = 0;
      PFN_vkCmdSetDiscardRectangleModeEXT   vkCmdSetDiscardRectangleModeEXT   = 0;

      //=== VK_EXT_hdr_metadata ===
      PFN_vkSetHdrMetadataEXT vkSetHdrMetadataEXT = 0;

      //=== VK_KHR_create_renderpass2 ===
      PFN_vkCreateRenderPass2KHR   vkCreateRenderPass2KHR   = 0;
      PFN_vkCmdBeginRenderPass2KHR vkCmdBeginRenderPass2KHR = 0;
      PFN_vkCmdNextSubpass2KHR     vkCmdNextSubpass2KHR     = 0;
      PFN_vkCmdEndRenderPass2KHR   vkCmdEndRenderPass2KHR   = 0;

      //=== VK_KHR_shared_presentable_image ===
      PFN_vkGetSwapchainStatusKHR vkGetSwapchainStatusKHR = 0;

      //=== VK_KHR_external_fence_capabilities ===
      PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR vkGetPhysicalDeviceExternalFencePropertiesKHR = 0;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
      //=== VK_KHR_external_fence_win32 ===
      PFN_vkImportFenceWin32HandleKHR vkImportFenceWin32HandleKHR = 0;
      PFN_vkGetFenceWin32HandleKHR    vkGetFenceWin32HandleKHR    = 0;
#else
      PFN_dummy vkImportFenceWin32HandleKHR_placeholder = 0;
      PFN_dummy vkGetFenceWin32HandleKHR_placeholder    = 0;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

      //=== VK_KHR_external_fence_fd ===
      PFN_vkImportFenceFdKHR vkImportFenceFdKHR = 0;
      PFN_vkGetFenceFdKHR    vkGetFenceFdKHR    = 0;

      //=== VK_KHR_performance_query ===
      PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = 0;
      PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR         vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR         = 0;
      PFN_vkAcquireProfilingLockKHR                                       vkAcquireProfilingLockKHR                                       = 0;
      PFN_vkReleaseProfilingLockKHR                                       vkReleaseProfilingLockKHR                                       = 0;

      //=== VK_KHR_get_surface_capabilities2 ===
      PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR vkGetPhysicalDeviceSurfaceCapabilities2KHR = 0;
      PFN_vkGetPhysicalDeviceSurfaceFormats2KHR      vkGetPhysicalDeviceSurfaceFormats2KHR      = 0;

      //=== VK_KHR_get_display_properties2 ===
      PFN_vkGetPhysicalDeviceDisplayProperties2KHR      vkGetPhysicalDeviceDisplayProperties2KHR      = 0;
      PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR vkGetPhysicalDeviceDisplayPlaneProperties2KHR = 0;
      PFN_vkGetDisplayModeProperties2KHR                vkGetDisplayModeProperties2KHR                = 0;
      PFN_vkGetDisplayPlaneCapabilities2KHR             vkGetDisplayPlaneCapabilities2KHR             = 0;

#if defined( VK_USE_PLATFORM_IOS_MVK )
      //=== VK_MVK_ios_surface ===
      PFN_vkCreateIOSSurfaceMVK vkCreateIOSSurfaceMVK = 0;
#else
      PFN_dummy vkCreateIOSSurfaceMVK_placeholder = 0;
#endif /*VK_USE_PLATFORM_IOS_MVK*/

#if defined( VK_USE_PLATFORM_MACOS_MVK )
      //=== VK_MVK_macos_surface ===
      PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK = 0;
#else
      PFN_dummy vkCreateMacOSSurfaceMVK_placeholder = 0;
#endif /*VK_USE_PLATFORM_MACOS_MVK*/

      //=== VK_EXT_debug_utils ===
      PFN_vkSetDebugUtilsObjectNameEXT    vkSetDebugUtilsObjectNameEXT    = 0;
      PFN_vkSetDebugUtilsObjectTagEXT     vkSetDebugUtilsObjectTagEXT     = 0;
      PFN_vkQueueBeginDebugUtilsLabelEXT  vkQueueBeginDebugUtilsLabelEXT  = 0;
      PFN_vkQueueEndDebugUtilsLabelEXT    vkQueueEndDebugUtilsLabelEXT    = 0;
      PFN_vkQueueInsertDebugUtilsLabelEXT vkQueueInsertDebugUtilsLabelEXT = 0;
      PFN_vkCmdBeginDebugUtilsLabelEXT    vkCmdBeginDebugUtilsLabelEXT    = 0;
      PFN_vkCmdEndDebugUtilsLabelEXT      vkCmdEndDebugUtilsLabelEXT      = 0;
      PFN_vkCmdInsertDebugUtilsLabelEXT   vkCmdInsertDebugUtilsLabelEXT   = 0;
      PFN_vkCreateDebugUtilsMessengerEXT  vkCreateDebugUtilsMessengerEXT  = 0;
      PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = 0;
      PFN_vkSubmitDebugUtilsMessageEXT    vkSubmitDebugUtilsMessageEXT    = 0;

#if defined( VK_USE_PLATFORM_ANDROID_KHR )
      //=== VK_ANDROID_external_memory_android_hardware_buffer ===
      PFN_vkGetAndroidHardwareBufferPropertiesANDROID vkGetAndroidHardwareBufferPropertiesANDROID = 0;
      PFN_vkGetMemoryAndroidHardwareBufferANDROID     vkGetMemoryAndroidHardwareBufferANDROID     = 0;
#else
      PFN_dummy vkGetAndroidHardwareBufferPropertiesANDROID_placeholder = 0;
      PFN_dummy vkGetMemoryAndroidHardwareBufferANDROID_placeholder     = 0;
#endif /*VK_USE_PLATFORM_ANDROID_KHR*/

      //=== VK_AMD_gpa_interface ===
      PFN_vkCreateGpaSessionAMD         vkCreateGpaSessionAMD         = 0;
      PFN_vkDestroyGpaSessionAMD        vkDestroyGpaSessionAMD        = 0;
      PFN_vkSetGpaDeviceClockModeAMD    vkSetGpaDeviceClockModeAMD    = 0;
      PFN_vkGetGpaDeviceClockInfoAMD    vkGetGpaDeviceClockInfoAMD    = 0;
      PFN_vkCmdBeginGpaSessionAMD       vkCmdBeginGpaSessionAMD       = 0;
      PFN_vkCmdEndGpaSessionAMD         vkCmdEndGpaSessionAMD         = 0;
      PFN_vkCmdBeginGpaSampleAMD        vkCmdBeginGpaSampleAMD        = 0;
      PFN_vkCmdEndGpaSampleAMD          vkCmdEndGpaSampleAMD          = 0;
      PFN_vkGetGpaSessionStatusAMD      vkGetGpaSessionStatusAMD      = 0;
      PFN_vkGetGpaSessionResultsAMD     vkGetGpaSessionResultsAMD     = 0;
      PFN_vkResetGpaSessionAMD          vkResetGpaSessionAMD          = 0;
      PFN_vkCmdCopyGpaSessionResultsAMD vkCmdCopyGpaSessionResultsAMD = 0;

#if defined( VK_ENABLE_BETA_EXTENSIONS )
      //=== VK_AMDX_shader_enqueue ===
      PFN_vkCreateExecutionGraphPipelinesAMDX        vkCreateExecutionGraphPipelinesAMDX        = 0;
      PFN_vkGetExecutionGraphPipelineScratchSizeAMDX vkGetExecutionGraphPipelineScratchSizeAMDX = 0;
      PFN_vkGetExecutionGraphPipelineNodeIndexAMDX   vkGetExecutionGraphPipelineNodeIndexAMDX   = 0;
      PFN_vkCmdInitializeGraphScratchMemoryAMDX      vkCmdInitializeGraphScratchMemoryAMDX      = 0;
      PFN_vkCmdDispatchGraphAMDX                     vkCmdDispatchGraphAMDX                     = 0;
      PFN_vkCmdDispatchGraphIndirectAMDX             vkCmdDispatchGraphIndirectAMDX             = 0;
      PFN_vkCmdDispatchGraphIndirectCountAMDX        vkCmdDispatchGraphIndirectCountAMDX        = 0;
#else
      PFN_dummy vkCreateExecutionGraphPipelinesAMDX_placeholder        = 0;
      PFN_dummy vkGetExecutionGraphPipelineScratchSizeAMDX_placeholder = 0;
      PFN_dummy vkGetExecutionGraphPipelineNodeIndexAMDX_placeholder   = 0;
      PFN_dummy vkCmdInitializeGraphScratchMemoryAMDX_placeholder      = 0;
      PFN_dummy vkCmdDispatchGraphAMDX_placeholder                     = 0;
      PFN_dummy vkCmdDispatchGraphIndirectAMDX_placeholder             = 0;
      PFN_dummy vkCmdDispatchGraphIndirectCountAMDX_placeholder        = 0;
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

      //=== VK_EXT_descriptor_heap ===
      PFN_vkWriteSamplerDescriptorsEXT         vkWriteSamplerDescriptorsEXT         = 0;
      PFN_vkWriteResourceDescriptorsEXT        vkWriteResourceDescriptorsEXT        = 0;
      PFN_vkCmdBindSamplerHeapEXT              vkCmdBindSamplerHeapEXT              = 0;
      PFN_vkCmdBindResourceHeapEXT             vkCmdBindResourceHeapEXT             = 0;
      PFN_vkCmdPushDataEXT                     vkCmdPushDataEXT                     = 0;
      PFN_vkGetImageOpaqueCaptureDataEXT       vkGetImageOpaqueCaptureDataEXT       = 0;
      PFN_vkGetPhysicalDeviceDescriptorSizeEXT vkGetPhysicalDeviceDescriptorSizeEXT = 0;
      PFN_vkRegisterCustomBorderColorEXT       vkRegisterCustomBorderColorEXT       = 0;
      PFN_vkUnregisterCustomBorderColorEXT     vkUnregisterCustomBorderColorEXT     = 0;
      PFN_vkGetTensorOpaqueCaptureDataARM      vkGetTensorOpaqueCaptureDataARM      = 0;

      //=== VK_EXT_sample_locations ===
      PFN_vkCmdSetSampleLocationsEXT                  vkCmdSetSampleLocationsEXT                  = 0;
      PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT vkGetPhysicalDeviceMultisamplePropertiesEXT = 0;

      //=== VK_KHR_get_memory_requirements2 ===
      PFN_vkGetImageMemoryRequirements2KHR       vkGetImageMemoryRequirements2KHR       = 0;
      PFN_vkGetBufferMemoryRequirements2KHR      vkGetBufferMemoryRequirements2KHR      = 0;
      PFN_vkGetImageSparseMemoryRequirements2KHR vkGetImageSparseMemoryRequirements2KHR = 0;

      //=== VK_KHR_acceleration_structure ===
      PFN_vkCreateAccelerationStructureKHR                 vkCreateAccelerationStructureKHR                 = 0;
      PFN_vkDestroyAccelerationStructureKHR                vkDestroyAccelerationStructureKHR                = 0;
      PFN_vkCmdBuildAccelerationStructuresKHR              vkCmdBuildAccelerationStructuresKHR              = 0;
      PFN_vkCmdBuildAccelerationStructuresIndirectKHR      vkCmdBuildAccelerationStructuresIndirectKHR      = 0;
      PFN_vkBuildAccelerationStructuresKHR                 vkBuildAccelerationStructuresKHR                 = 0;
      PFN_vkCopyAccelerationStructureKHR                   vkCopyAccelerationStructureKHR                   = 0;
      PFN_vkCopyAccelerationStructureToMemoryKHR           vkCopyAccelerationStructureToMemoryKHR           = 0;
      PFN_vkCopyMemoryToAccelerationStructureKHR           vkCopyMemoryToAccelerationStructureKHR           = 0;
      PFN_vkWriteAccelerationStructuresPropertiesKHR       vkWriteAccelerationStructuresPropertiesKHR       = 0;
      PFN_vkCmdCopyAccelerationStructureKHR                vkCmdCopyAccelerationStructureKHR                = 0;
      PFN_vkCmdCopyAccelerationStructureToMemoryKHR        vkCmdCopyAccelerationStructureToMemoryKHR        = 0;
      PFN_vkCmdCopyMemoryToAccelerationStructureKHR        vkCmdCopyMemoryToAccelerationStructureKHR        = 0;
      PFN_vkGetAccelerationStructureDeviceAddressKHR       vkGetAccelerationStructureDeviceAddressKHR       = 0;
      PFN_vkCmdWriteAccelerationStructuresPropertiesKHR    vkCmdWriteAccelerationStructuresPropertiesKHR    = 0;
      PFN_vkGetDeviceAccelerationStructureCompatibilityKHR vkGetDeviceAccelerationStructureCompatibilityKHR = 0;
      PFN_vkGetAccelerationStructureBuildSizesKHR          vkGetAccelerationStructureBuildSizesKHR          = 0;

      //=== VK_KHR_ray_tracing_pipeline ===
      PFN_vkCmdTraceRaysKHR                                 vkCmdTraceRaysKHR                                 = 0;
      PFN_vkCreateRayTracingPipelinesKHR                    vkCreateRayTracingPipelinesKHR                    = 0;
      PFN_vkGetRayTracingShaderGroupHandlesKHR              vkGetRayTracingShaderGroupHandlesKHR              = 0;
      PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR vkGetRayTracingCaptureReplayShaderGroupHandlesKHR = 0;
      PFN_vkCmdTraceRaysIndirectKHR                         vkCmdTraceRaysIndirectKHR                         = 0;
      PFN_vkGetRayTracingShaderGroupStackSizeKHR            vkGetRayTracingShaderGroupStackSizeKHR            = 0;
      PFN_vkCmdSetRayTracingPipelineStackSizeKHR            vkCmdSetRayTracingPipelineStackSizeKHR            = 0;

      //=== VK_KHR_sampler_ycbcr_conversion ===
      PFN_vkCreateSamplerYcbcrConversionKHR  vkCreateSamplerYcbcrConversionKHR  = 0;
      PFN_vkDestroySamplerYcbcrConversionKHR vkDestroySamplerYcbcrConversionKHR = 0;

      //=== VK_KHR_bind_memory2 ===
      PFN_vkBindBufferMemory2KHR vkBindBufferMemory2KHR = 0;
      PFN_vkBindImageMemory2KHR  vkBindImageMemory2KHR  = 0;

      //=== VK_EXT_image_drm_format_modifier ===
      PFN_vkGetImageDrmFormatModifierPropertiesEXT vkGetImageDrmFormatModifierPropertiesEXT = 0;

      //=== VK_EXT_validation_cache ===
      PFN_vkCreateValidationCacheEXT  vkCreateValidationCacheEXT  = 0;
      PFN_vkDestroyValidationCacheEXT vkDestroyValidationCacheEXT = 0;
      PFN_vkMergeValidationCachesEXT  vkMergeValidationCachesEXT  = 0;
      PFN_vkGetValidationCacheDataEXT vkGetValidationCacheDataEXT = 0;

      //=== VK_NV_shading_rate_image ===
      PFN_vkCmdBindShadingRateImageNV          vkCmdBindShadingRateImageNV          = 0;
      PFN_vkCmdSetViewportShadingRatePaletteNV vkCmdSetViewportShadingRatePaletteNV = 0;
      PFN_vkCmdSetCoarseSampleOrderNV          vkCmdSetCoarseSampleOrderNV          = 0;

      //=== VK_NV_ray_tracing ===
      PFN_vkCreateAccelerationStructureNV                vkCreateAccelerationStructureNV                = 0;
      PFN_vkDestroyAccelerationStructureNV               vkDestroyAccelerationStructureNV               = 0;
      PFN_vkGetAccelerationStructureMemoryRequirementsNV vkGetAccelerationStructureMemoryRequirementsNV = 0;
      PFN_vkBindAccelerationStructureMemoryNV            vkBindAccelerationStructureMemoryNV            = 0;
      PFN_vkCmdBuildAccelerationStructureNV              vkCmdBuildAccelerationStructureNV              = 0;
      PFN_vkCmdCopyAccelerationStructureNV               vkCmdCopyAccelerationStructureNV               = 0;
      PFN_vkCmdTraceRaysNV                               vkCmdTraceRaysNV                               = 0;
      PFN_vkCreateRayTracingPipelinesNV                  vkCreateRayTracingPipelinesNV                  = 0;
      PFN_vkGetRayTracingShaderGroupHandlesNV            vkGetRayTracingShaderGroupHandlesNV            = 0;
      PFN_vkGetAccelerationStructureHandleNV             vkGetAccelerationStructureHandleNV             = 0;
      PFN_vkCmdWriteAccelerationStructuresPropertiesNV   vkCmdWriteAccelerationStructuresPropertiesNV   = 0;
      PFN_vkCompileDeferredNV                            vkCompileDeferredNV                            = 0;

      //=== VK_KHR_maintenance3 ===
      PFN_vkGetDescriptorSetLayoutSupportKHR vkGetDescriptorSetLayoutSupportKHR = 0;

      //=== VK_KHR_draw_indirect_count ===
      PFN_vkCmdDrawIndirectCountKHR        vkCmdDrawIndirectCountKHR        = 0;
      PFN_vkCmdDrawIndexedIndirectCountKHR vkCmdDrawIndexedIndirectCountKHR = 0;

      //=== VK_EXT_external_memory_host ===
      PFN_vkGetMemoryHostPointerPropertiesEXT vkGetMemoryHostPointerPropertiesEXT = 0;

      //=== VK_AMD_buffer_marker ===
      PFN_vkCmdWriteBufferMarkerAMD  vkCmdWriteBufferMarkerAMD  = 0;
      PFN_vkCmdWriteBufferMarker2AMD vkCmdWriteBufferMarker2AMD = 0;

      //=== VK_EXT_calibrated_timestamps ===
      PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT vkGetPhysicalDeviceCalibrateableTimeDomainsEXT = 0;
      PFN_vkGetCalibratedTimestampsEXT                   vkGetCalibratedTimestampsEXT                   = 0;

      //=== VK_NV_mesh_shader ===
      PFN_vkCmdDrawMeshTasksNV              vkCmdDrawMeshTasksNV              = 0;
      PFN_vkCmdDrawMeshTasksIndirectNV      vkCmdDrawMeshTasksIndirectNV      = 0;
      PFN_vkCmdDrawMeshTasksIndirectCountNV vkCmdDrawMeshTasksIndirectCountNV = 0;

      //=== VK_NV_scissor_exclusive ===
      PFN_vkCmdSetExclusiveScissorEnableNV vkCmdSetExclusiveScissorEnableNV = 0;
      PFN_vkCmdSetExclusiveScissorNV       vkCmdSetExclusiveScissorNV       = 0;

      //=== VK_NV_device_diagnostic_checkpoints ===
      PFN_vkCmdSetCheckpointNV        vkCmdSetCheckpointNV        = 0;
      PFN_vkGetQueueCheckpointDataNV  vkGetQueueCheckpointDataNV  = 0;
      PFN_vkGetQueueCheckpointData2NV vkGetQueueCheckpointData2NV = 0;

      //=== VK_KHR_timeline_semaphore ===
      PFN_vkGetSemaphoreCounterValueKHR vkGetSemaphoreCounterValueKHR = 0;
      PFN_vkWaitSemaphoresKHR           vkWaitSemaphoresKHR           = 0;
      PFN_vkSignalSemaphoreKHR          vkSignalSemaphoreKHR          = 0;

      //=== VK_EXT_present_timing ===
      PFN_vkSetSwapchainPresentTimingQueueSizeEXT vkSetSwapchainPresentTimingQueueSizeEXT = 0;
      PFN_vkGetSwapchainTimingPropertiesEXT       vkGetSwapchainTimingPropertiesEXT       = 0;
      PFN_vkGetSwapchainTimeDomainPropertiesEXT   vkGetSwapchainTimeDomainPropertiesEXT   = 0;
      PFN_vkGetPastPresentationTimingEXT          vkGetPastPresentationTimingEXT          = 0;

      //=== VK_INTEL_performance_query ===
      PFN_vkInitializePerformanceApiINTEL         vkInitializePerformanceApiINTEL         = 0;
      PFN_vkUninitializePerformanceApiINTEL       vkUninitializePerformanceApiINTEL       = 0;
      PFN_vkCmdSetPerformanceMarkerINTEL          vkCmdSetPerformanceMarkerINTEL          = 0;
      PFN_vkCmdSetPerformanceStreamMarkerINTEL    vkCmdSetPerformanceStreamMarkerINTEL    = 0;
      PFN_vkCmdSetPerformanceOverrideINTEL        vkCmdSetPerformanceOverrideINTEL        = 0;
      PFN_vkAcquirePerformanceConfigurationINTEL  vkAcquirePerformanceConfigurationINTEL  = 0;
      PFN_vkReleasePerformanceConfigurationINTEL  vkReleasePerformanceConfigurationINTEL  = 0;
      PFN_vkQueueSetPerformanceConfigurationINTEL vkQueueSetPerformanceConfigurationINTEL = 0;
      PFN_vkGetPerformanceParameterINTEL          vkGetPerformanceParameterINTEL          = 0;

      //=== VK_AMD_display_native_hdr ===
      PFN_vkSetLocalDimmingAMD vkSetLocalDimmingAMD = 0;

#if defined( VK_USE_PLATFORM_FUCHSIA )
      //=== VK_FUCHSIA_imagepipe_surface ===
      PFN_vkCreateImagePipeSurfaceFUCHSIA vkCreateImagePipeSurfaceFUCHSIA = 0;
#else
      PFN_dummy vkCreateImagePipeSurfaceFUCHSIA_placeholder = 0;
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_METAL_EXT )
      //=== VK_EXT_metal_surface ===
      PFN_vkCreateMetalSurfaceEXT vkCreateMetalSurfaceEXT = 0;
#else
      PFN_dummy vkCreateMetalSurfaceEXT_placeholder = 0;
#endif /*VK_USE_PLATFORM_METAL_EXT*/

      //=== VK_KHR_fragment_shading_rate ===
      PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR vkGetPhysicalDeviceFragmentShadingRatesKHR = 0;
      PFN_vkCmdSetFragmentShadingRateKHR             vkCmdSetFragmentShadingRateKHR             = 0;

      //=== VK_KHR_dynamic_rendering_local_read ===
      PFN_vkCmdSetRenderingAttachmentLocationsKHR    vkCmdSetRenderingAttachmentLocationsKHR    = 0;
      PFN_vkCmdSetRenderingInputAttachmentIndicesKHR vkCmdSetRenderingInputAttachmentIndicesKHR = 0;

      //=== VK_EXT_buffer_device_address ===
      PFN_vkGetBufferDeviceAddressEXT vkGetBufferDeviceAddressEXT = 0;

      //=== VK_EXT_tooling_info ===
      PFN_vkGetPhysicalDeviceToolPropertiesEXT vkGetPhysicalDeviceToolPropertiesEXT = 0;

      //=== VK_KHR_present_wait ===
      PFN_vkWaitForPresentKHR vkWaitForPresentKHR = 0;

      //=== VK_NV_cooperative_matrix ===
      PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV vkGetPhysicalDeviceCooperativeMatrixPropertiesNV = 0;

      //=== VK_NV_coverage_reduction_mode ===
      PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = 0;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
      //=== VK_EXT_full_screen_exclusive ===
      PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT vkGetPhysicalDeviceSurfacePresentModes2EXT = 0;
      PFN_vkAcquireFullScreenExclusiveModeEXT        vkAcquireFullScreenExclusiveModeEXT        = 0;
      PFN_vkReleaseFullScreenExclusiveModeEXT        vkReleaseFullScreenExclusiveModeEXT        = 0;
      PFN_vkGetDeviceGroupSurfacePresentModes2EXT    vkGetDeviceGroupSurfacePresentModes2EXT    = 0;
#else
      PFN_dummy vkGetPhysicalDeviceSurfacePresentModes2EXT_placeholder = 0;
      PFN_dummy vkAcquireFullScreenExclusiveModeEXT_placeholder        = 0;
      PFN_dummy vkReleaseFullScreenExclusiveModeEXT_placeholder        = 0;
      PFN_dummy vkGetDeviceGroupSurfacePresentModes2EXT_placeholder    = 0;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

      //=== VK_EXT_headless_surface ===
      PFN_vkCreateHeadlessSurfaceEXT vkCreateHeadlessSurfaceEXT = 0;

      //=== VK_KHR_buffer_device_address ===
      PFN_vkGetBufferDeviceAddressKHR              vkGetBufferDeviceAddressKHR              = 0;
      PFN_vkGetBufferOpaqueCaptureAddressKHR       vkGetBufferOpaqueCaptureAddressKHR       = 0;
      PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR vkGetDeviceMemoryOpaqueCaptureAddressKHR = 0;

      //=== VK_EXT_line_rasterization ===
      PFN_vkCmdSetLineStippleEXT vkCmdSetLineStippleEXT = 0;

      //=== VK_EXT_host_query_reset ===
      PFN_vkResetQueryPoolEXT vkResetQueryPoolEXT = 0;

      //=== VK_EXT_extended_dynamic_state ===
      PFN_vkCmdSetCullModeEXT              vkCmdSetCullModeEXT              = 0;
      PFN_vkCmdSetFrontFaceEXT             vkCmdSetFrontFaceEXT             = 0;
      PFN_vkCmdSetPrimitiveTopologyEXT     vkCmdSetPrimitiveTopologyEXT     = 0;
      PFN_vkCmdSetViewportWithCountEXT     vkCmdSetViewportWithCountEXT     = 0;
      PFN_vkCmdSetScissorWithCountEXT      vkCmdSetScissorWithCountEXT      = 0;
      PFN_vkCmdBindVertexBuffers2EXT       vkCmdBindVertexBuffers2EXT       = 0;
      PFN_vkCmdSetDepthTestEnableEXT       vkCmdSetDepthTestEnableEXT       = 0;
      PFN_vkCmdSetDepthWriteEnableEXT      vkCmdSetDepthWriteEnableEXT      = 0;
      PFN_vkCmdSetDepthCompareOpEXT        vkCmdSetDepthCompareOpEXT        = 0;
      PFN_vkCmdSetDepthBoundsTestEnableEXT vkCmdSetDepthBoundsTestEnableEXT = 0;
      PFN_vkCmdSetStencilTestEnableEXT     vkCmdSetStencilTestEnableEXT     = 0;
      PFN_vkCmdSetStencilOpEXT             vkCmdSetStencilOpEXT             = 0;

      //=== VK_KHR_deferred_host_operations ===
      PFN_vkCreateDeferredOperationKHR            vkCreateDeferredOperationKHR            = 0;
      PFN_vkDestroyDeferredOperationKHR           vkDestroyDeferredOperationKHR           = 0;
      PFN_vkGetDeferredOperationMaxConcurrencyKHR vkGetDeferredOperationMaxConcurrencyKHR = 0;
      PFN_vkGetDeferredOperationResultKHR         vkGetDeferredOperationResultKHR         = 0;
      PFN_vkDeferredOperationJoinKHR              vkDeferredOperationJoinKHR              = 0;

      //=== VK_KHR_pipeline_executable_properties ===
      PFN_vkGetPipelineExecutablePropertiesKHR              vkGetPipelineExecutablePropertiesKHR              = 0;
      PFN_vkGetPipelineExecutableStatisticsKHR              vkGetPipelineExecutableStatisticsKHR              = 0;
      PFN_vkGetPipelineExecutableInternalRepresentationsKHR vkGetPipelineExecutableInternalRepresentationsKHR = 0;

      //=== VK_EXT_host_image_copy ===
      PFN_vkCopyMemoryToImageEXT          vkCopyMemoryToImageEXT          = 0;
      PFN_vkCopyImageToMemoryEXT          vkCopyImageToMemoryEXT          = 0;
      PFN_vkCopyImageToImageEXT           vkCopyImageToImageEXT           = 0;
      PFN_vkTransitionImageLayoutEXT      vkTransitionImageLayoutEXT      = 0;
      PFN_vkGetImageSubresourceLayout2EXT vkGetImageSubresourceLayout2EXT = 0;

      //=== VK_KHR_map_memory2 ===
      PFN_vkMapMemory2KHR   vkMapMemory2KHR   = 0;
      PFN_vkUnmapMemory2KHR vkUnmapMemory2KHR = 0;

      //=== VK_EXT_swapchain_maintenance1 ===
      PFN_vkReleaseSwapchainImagesEXT vkReleaseSwapchainImagesEXT = 0;

      //=== VK_NV_device_generated_commands ===
      PFN_vkGetGeneratedCommandsMemoryRequirementsNV vkGetGeneratedCommandsMemoryRequirementsNV = 0;
      PFN_vkCmdPreprocessGeneratedCommandsNV         vkCmdPreprocessGeneratedCommandsNV         = 0;
      PFN_vkCmdExecuteGeneratedCommandsNV            vkCmdExecuteGeneratedCommandsNV            = 0;
      PFN_vkCmdBindPipelineShaderGroupNV             vkCmdBindPipelineShaderGroupNV             = 0;
      PFN_vkCreateIndirectCommandsLayoutNV           vkCreateIndirectCommandsLayoutNV           = 0;
      PFN_vkDestroyIndirectCommandsLayoutNV          vkDestroyIndirectCommandsLayoutNV          = 0;

      //=== VK_EXT_depth_bias_control ===
      PFN_vkCmdSetDepthBias2EXT vkCmdSetDepthBias2EXT = 0;

      //=== VK_EXT_acquire_drm_display ===
      PFN_vkAcquireDrmDisplayEXT vkAcquireDrmDisplayEXT = 0;
      PFN_vkGetDrmDisplayEXT     vkGetDrmDisplayEXT     = 0;

      //=== VK_EXT_private_data ===
      PFN_vkCreatePrivateDataSlotEXT  vkCreatePrivateDataSlotEXT  = 0;
      PFN_vkDestroyPrivateDataSlotEXT vkDestroyPrivateDataSlotEXT = 0;
      PFN_vkSetPrivateDataEXT         vkSetPrivateDataEXT         = 0;
      PFN_vkGetPrivateDataEXT         vkGetPrivateDataEXT         = 0;

      //=== VK_KHR_video_encode_queue ===
      PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = 0;
      PFN_vkGetEncodedVideoSessionParametersKHR                   vkGetEncodedVideoSessionParametersKHR                   = 0;
      PFN_vkCmdEncodeVideoKHR                                     vkCmdEncodeVideoKHR                                     = 0;

      //=== VK_QCOM_queue_perf_hint ===
      PFN_vkQueueSetPerfHintQCOM vkQueueSetPerfHintQCOM = 0;

#if defined( VK_ENABLE_BETA_EXTENSIONS )
      //=== VK_NV_cuda_kernel_launch ===
      PFN_vkCreateCudaModuleNV    vkCreateCudaModuleNV    = 0;
      PFN_vkGetCudaModuleCacheNV  vkGetCudaModuleCacheNV  = 0;
      PFN_vkCreateCudaFunctionNV  vkCreateCudaFunctionNV  = 0;
      PFN_vkDestroyCudaModuleNV   vkDestroyCudaModuleNV   = 0;
      PFN_vkDestroyCudaFunctionNV vkDestroyCudaFunctionNV = 0;
      PFN_vkCmdCudaLaunchKernelNV vkCmdCudaLaunchKernelNV = 0;
#else
      PFN_dummy vkCreateCudaModuleNV_placeholder    = 0;
      PFN_dummy vkGetCudaModuleCacheNV_placeholder  = 0;
      PFN_dummy vkCreateCudaFunctionNV_placeholder  = 0;
      PFN_dummy vkDestroyCudaModuleNV_placeholder   = 0;
      PFN_dummy vkDestroyCudaFunctionNV_placeholder = 0;
      PFN_dummy vkCmdCudaLaunchKernelNV_placeholder = 0;
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

      //=== VK_QCOM_tile_shading ===
      PFN_vkCmdDispatchTileQCOM          vkCmdDispatchTileQCOM          = 0;
      PFN_vkCmdBeginPerTileExecutionQCOM vkCmdBeginPerTileExecutionQCOM = 0;
      PFN_vkCmdEndPerTileExecutionQCOM   vkCmdEndPerTileExecutionQCOM   = 0;

#if defined( VK_USE_PLATFORM_METAL_EXT )
      //=== VK_EXT_metal_objects ===
      PFN_vkExportMetalObjectsEXT vkExportMetalObjectsEXT = 0;
#else
      PFN_dummy vkExportMetalObjectsEXT_placeholder = 0;
#endif /*VK_USE_PLATFORM_METAL_EXT*/

      //=== VK_KHR_synchronization2 ===
      PFN_vkCmdSetEvent2KHR        vkCmdSetEvent2KHR        = 0;
      PFN_vkCmdResetEvent2KHR      vkCmdResetEvent2KHR      = 0;
      PFN_vkCmdWaitEvents2KHR      vkCmdWaitEvents2KHR      = 0;
      PFN_vkCmdPipelineBarrier2KHR vkCmdPipelineBarrier2KHR = 0;
      PFN_vkCmdWriteTimestamp2KHR  vkCmdWriteTimestamp2KHR  = 0;
      PFN_vkQueueSubmit2KHR        vkQueueSubmit2KHR        = 0;

      //=== VK_EXT_descriptor_buffer ===
      PFN_vkGetDescriptorSetLayoutSizeEXT                          vkGetDescriptorSetLayoutSizeEXT                          = 0;
      PFN_vkGetDescriptorSetLayoutBindingOffsetEXT                 vkGetDescriptorSetLayoutBindingOffsetEXT                 = 0;
      PFN_vkGetDescriptorEXT                                       vkGetDescriptorEXT                                       = 0;
      PFN_vkCmdBindDescriptorBuffersEXT                            vkCmdBindDescriptorBuffersEXT                            = 0;
      PFN_vkCmdSetDescriptorBufferOffsetsEXT                       vkCmdSetDescriptorBufferOffsetsEXT                       = 0;
      PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT             vkCmdBindDescriptorBufferEmbeddedSamplersEXT             = 0;
      PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT                vkGetBufferOpaqueCaptureDescriptorDataEXT                = 0;
      PFN_vkGetImageOpaqueCaptureDescriptorDataEXT                 vkGetImageOpaqueCaptureDescriptorDataEXT                 = 0;
      PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT             vkGetImageViewOpaqueCaptureDescriptorDataEXT             = 0;
      PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT               vkGetSamplerOpaqueCaptureDescriptorDataEXT               = 0;
      PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = 0;

      //=== VK_KHR_device_address_commands ===
      PFN_vkCmdBindIndexBuffer3KHR              vkCmdBindIndexBuffer3KHR              = 0;
      PFN_vkCmdBindVertexBuffers3KHR            vkCmdBindVertexBuffers3KHR            = 0;
      PFN_vkCmdDrawIndirect2KHR                 vkCmdDrawIndirect2KHR                 = 0;
      PFN_vkCmdDrawIndexedIndirect2KHR          vkCmdDrawIndexedIndirect2KHR          = 0;
      PFN_vkCmdDispatchIndirect2KHR             vkCmdDispatchIndirect2KHR             = 0;
      PFN_vkCmdCopyMemoryKHR                    vkCmdCopyMemoryKHR                    = 0;
      PFN_vkCmdCopyMemoryToImageKHR             vkCmdCopyMemoryToImageKHR             = 0;
      PFN_vkCmdCopyImageToMemoryKHR             vkCmdCopyImageToMemoryKHR             = 0;
      PFN_vkCmdUpdateMemoryKHR                  vkCmdUpdateMemoryKHR                  = 0;
      PFN_vkCmdFillMemoryKHR                    vkCmdFillMemoryKHR                    = 0;
      PFN_vkCmdCopyQueryPoolResultsToMemoryKHR  vkCmdCopyQueryPoolResultsToMemoryKHR  = 0;
      PFN_vkCmdDrawIndirectCount2KHR            vkCmdDrawIndirectCount2KHR            = 0;
      PFN_vkCmdDrawIndexedIndirectCount2KHR     vkCmdDrawIndexedIndirectCount2KHR     = 0;
      PFN_vkCmdBeginConditionalRendering2EXT    vkCmdBeginConditionalRendering2EXT    = 0;
      PFN_vkCmdBindTransformFeedbackBuffers2EXT vkCmdBindTransformFeedbackBuffers2EXT = 0;
      PFN_vkCmdBeginTransformFeedback2EXT       vkCmdBeginTransformFeedback2EXT       = 0;
      PFN_vkCmdEndTransformFeedback2EXT         vkCmdEndTransformFeedback2EXT         = 0;
      PFN_vkCmdDrawIndirectByteCount2EXT        vkCmdDrawIndirectByteCount2EXT        = 0;
      PFN_vkCmdDrawMeshTasksIndirect2EXT        vkCmdDrawMeshTasksIndirect2EXT        = 0;
      PFN_vkCmdDrawMeshTasksIndirectCount2EXT   vkCmdDrawMeshTasksIndirectCount2EXT   = 0;
      PFN_vkCmdWriteMarkerToMemoryAMD           vkCmdWriteMarkerToMemoryAMD           = 0;
      PFN_vkCreateAccelerationStructure2KHR     vkCreateAccelerationStructure2KHR     = 0;

      //=== VK_NV_fragment_shading_rate_enums ===
      PFN_vkCmdSetFragmentShadingRateEnumNV vkCmdSetFragmentShadingRateEnumNV = 0;

      //=== VK_EXT_mesh_shader ===
      PFN_vkCmdDrawMeshTasksEXT              vkCmdDrawMeshTasksEXT              = 0;
      PFN_vkCmdDrawMeshTasksIndirectEXT      vkCmdDrawMeshTasksIndirectEXT      = 0;
      PFN_vkCmdDrawMeshTasksIndirectCountEXT vkCmdDrawMeshTasksIndirectCountEXT = 0;

      //=== VK_KHR_copy_commands2 ===
      PFN_vkCmdCopyBuffer2KHR        vkCmdCopyBuffer2KHR        = 0;
      PFN_vkCmdCopyImage2KHR         vkCmdCopyImage2KHR         = 0;
      PFN_vkCmdCopyBufferToImage2KHR vkCmdCopyBufferToImage2KHR = 0;
      PFN_vkCmdCopyImageToBuffer2KHR vkCmdCopyImageToBuffer2KHR = 0;
      PFN_vkCmdBlitImage2KHR         vkCmdBlitImage2KHR         = 0;
      PFN_vkCmdResolveImage2KHR      vkCmdResolveImage2KHR      = 0;

      //=== VK_EXT_device_fault ===
      PFN_vkGetDeviceFaultInfoEXT vkGetDeviceFaultInfoEXT = 0;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
      //=== VK_NV_acquire_winrt_display ===
      PFN_vkAcquireWinrtDisplayNV vkAcquireWinrtDisplayNV = 0;
      PFN_vkGetWinrtDisplayNV     vkGetWinrtDisplayNV     = 0;
#else
      PFN_dummy vkAcquireWinrtDisplayNV_placeholder = 0;
      PFN_dummy vkGetWinrtDisplayNV_placeholder     = 0;
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

#if defined( VK_USE_PLATFORM_DIRECTFB_EXT )
      //=== VK_EXT_directfb_surface ===
      PFN_vkCreateDirectFBSurfaceEXT                        vkCreateDirectFBSurfaceEXT                        = 0;
      PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT vkGetPhysicalDeviceDirectFBPresentationSupportEXT = 0;
#else
      PFN_dummy vkCreateDirectFBSurfaceEXT_placeholder                        = 0;
      PFN_dummy vkGetPhysicalDeviceDirectFBPresentationSupportEXT_placeholder = 0;
#endif /*VK_USE_PLATFORM_DIRECTFB_EXT*/

      //=== VK_EXT_vertex_input_dynamic_state ===
      PFN_vkCmdSetVertexInputEXT vkCmdSetVertexInputEXT = 0;

#if defined( VK_USE_PLATFORM_FUCHSIA )
      //=== VK_FUCHSIA_external_memory ===
      PFN_vkGetMemoryZirconHandleFUCHSIA           vkGetMemoryZirconHandleFUCHSIA           = 0;
      PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA vkGetMemoryZirconHandlePropertiesFUCHSIA = 0;
#else
      PFN_dummy vkGetMemoryZirconHandleFUCHSIA_placeholder           = 0;
      PFN_dummy vkGetMemoryZirconHandlePropertiesFUCHSIA_placeholder = 0;
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
      //=== VK_FUCHSIA_external_semaphore ===
      PFN_vkImportSemaphoreZirconHandleFUCHSIA vkImportSemaphoreZirconHandleFUCHSIA = 0;
      PFN_vkGetSemaphoreZirconHandleFUCHSIA    vkGetSemaphoreZirconHandleFUCHSIA    = 0;
#else
      PFN_dummy vkImportSemaphoreZirconHandleFUCHSIA_placeholder = 0;
      PFN_dummy vkGetSemaphoreZirconHandleFUCHSIA_placeholder    = 0;
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
      //=== VK_FUCHSIA_buffer_collection ===
      PFN_vkCreateBufferCollectionFUCHSIA               vkCreateBufferCollectionFUCHSIA               = 0;
      PFN_vkSetBufferCollectionImageConstraintsFUCHSIA  vkSetBufferCollectionImageConstraintsFUCHSIA  = 0;
      PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA vkSetBufferCollectionBufferConstraintsFUCHSIA = 0;
      PFN_vkDestroyBufferCollectionFUCHSIA              vkDestroyBufferCollectionFUCHSIA              = 0;
      PFN_vkGetBufferCollectionPropertiesFUCHSIA        vkGetBufferCollectionPropertiesFUCHSIA        = 0;
#else
      PFN_dummy vkCreateBufferCollectionFUCHSIA_placeholder               = 0;
      PFN_dummy vkSetBufferCollectionImageConstraintsFUCHSIA_placeholder  = 0;
      PFN_dummy vkSetBufferCollectionBufferConstraintsFUCHSIA_placeholder = 0;
      PFN_dummy vkDestroyBufferCollectionFUCHSIA_placeholder              = 0;
      PFN_dummy vkGetBufferCollectionPropertiesFUCHSIA_placeholder        = 0;
#endif /*VK_USE_PLATFORM_FUCHSIA*/

      //=== VK_HUAWEI_subpass_shading ===
      PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI = 0;
      PFN_vkCmdSubpassShadingHUAWEI                       vkCmdSubpassShadingHUAWEI                       = 0;

      //=== VK_HUAWEI_invocation_mask ===
      PFN_vkCmdBindInvocationMaskHUAWEI vkCmdBindInvocationMaskHUAWEI = 0;

      //=== VK_NV_external_memory_rdma ===
      PFN_vkGetMemoryRemoteAddressNV vkGetMemoryRemoteAddressNV = 0;

      //=== VK_EXT_pipeline_properties ===
      PFN_vkGetPipelinePropertiesEXT vkGetPipelinePropertiesEXT = 0;

      //=== VK_EXT_extended_dynamic_state2 ===
      PFN_vkCmdSetPatchControlPointsEXT      vkCmdSetPatchControlPointsEXT      = 0;
      PFN_vkCmdSetRasterizerDiscardEnableEXT vkCmdSetRasterizerDiscardEnableEXT = 0;
      PFN_vkCmdSetDepthBiasEnableEXT         vkCmdSetDepthBiasEnableEXT         = 0;
      PFN_vkCmdSetLogicOpEXT                 vkCmdSetLogicOpEXT                 = 0;
      PFN_vkCmdSetPrimitiveRestartEnableEXT  vkCmdSetPrimitiveRestartEnableEXT  = 0;

#if defined( VK_USE_PLATFORM_SCREEN_QNX )
      //=== VK_QNX_screen_surface ===
      PFN_vkCreateScreenSurfaceQNX                        vkCreateScreenSurfaceQNX                        = 0;
      PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX vkGetPhysicalDeviceScreenPresentationSupportQNX = 0;
#else
      PFN_dummy vkCreateScreenSurfaceQNX_placeholder                        = 0;
      PFN_dummy vkGetPhysicalDeviceScreenPresentationSupportQNX_placeholder = 0;
#endif /*VK_USE_PLATFORM_SCREEN_QNX*/

      //=== VK_EXT_color_write_enable ===
      PFN_vkCmdSetColorWriteEnableEXT vkCmdSetColorWriteEnableEXT = 0;

      //=== VK_KHR_ray_tracing_maintenance1 ===
      PFN_vkCmdTraceRaysIndirect2KHR vkCmdTraceRaysIndirect2KHR = 0;

      //=== VK_EXT_multi_draw ===
      PFN_vkCmdDrawMultiEXT        vkCmdDrawMultiEXT        = 0;
      PFN_vkCmdDrawMultiIndexedEXT vkCmdDrawMultiIndexedEXT = 0;

      //=== VK_EXT_opacity_micromap ===
      PFN_vkCreateMicromapEXT                 vkCreateMicromapEXT                 = 0;
      PFN_vkDestroyMicromapEXT                vkDestroyMicromapEXT                = 0;
      PFN_vkCmdBuildMicromapsEXT              vkCmdBuildMicromapsEXT              = 0;
      PFN_vkBuildMicromapsEXT                 vkBuildMicromapsEXT                 = 0;
      PFN_vkCopyMicromapEXT                   vkCopyMicromapEXT                   = 0;
      PFN_vkCopyMicromapToMemoryEXT           vkCopyMicromapToMemoryEXT           = 0;
      PFN_vkCopyMemoryToMicromapEXT           vkCopyMemoryToMicromapEXT           = 0;
      PFN_vkWriteMicromapsPropertiesEXT       vkWriteMicromapsPropertiesEXT       = 0;
      PFN_vkCmdCopyMicromapEXT                vkCmdCopyMicromapEXT                = 0;
      PFN_vkCmdCopyMicromapToMemoryEXT        vkCmdCopyMicromapToMemoryEXT        = 0;
      PFN_vkCmdCopyMemoryToMicromapEXT        vkCmdCopyMemoryToMicromapEXT        = 0;
      PFN_vkCmdWriteMicromapsPropertiesEXT    vkCmdWriteMicromapsPropertiesEXT    = 0;
      PFN_vkGetDeviceMicromapCompatibilityEXT vkGetDeviceMicromapCompatibilityEXT = 0;
      PFN_vkGetMicromapBuildSizesEXT          vkGetMicromapBuildSizesEXT          = 0;

      //=== VK_HUAWEI_cluster_culling_shader ===
      PFN_vkCmdDrawClusterHUAWEI         vkCmdDrawClusterHUAWEI         = 0;
      PFN_vkCmdDrawClusterIndirectHUAWEI vkCmdDrawClusterIndirectHUAWEI = 0;

      //=== VK_EXT_pageable_device_local_memory ===
      PFN_vkSetDeviceMemoryPriorityEXT vkSetDeviceMemoryPriorityEXT = 0;

      //=== VK_KHR_maintenance4 ===
      PFN_vkGetDeviceBufferMemoryRequirementsKHR      vkGetDeviceBufferMemoryRequirementsKHR      = 0;
      PFN_vkGetDeviceImageMemoryRequirementsKHR       vkGetDeviceImageMemoryRequirementsKHR       = 0;
      PFN_vkGetDeviceImageSparseMemoryRequirementsKHR vkGetDeviceImageSparseMemoryRequirementsKHR = 0;

      //=== VK_ARM_scheduling_controls ===
      PFN_vkCmdSetDispatchParametersARM vkCmdSetDispatchParametersARM = 0;

      //=== VK_VALVE_descriptor_set_host_mapping ===
      PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE vkGetDescriptorSetLayoutHostMappingInfoVALVE = 0;
      PFN_vkGetDescriptorSetHostMappingVALVE           vkGetDescriptorSetHostMappingVALVE           = 0;

      //=== VK_NV_copy_memory_indirect ===
      PFN_vkCmdCopyMemoryIndirectNV        vkCmdCopyMemoryIndirectNV        = 0;
      PFN_vkCmdCopyMemoryToImageIndirectNV vkCmdCopyMemoryToImageIndirectNV = 0;

      //=== VK_NV_memory_decompression ===
      PFN_vkCmdDecompressMemoryNV              vkCmdDecompressMemoryNV              = 0;
      PFN_vkCmdDecompressMemoryIndirectCountNV vkCmdDecompressMemoryIndirectCountNV = 0;

      //=== VK_NV_device_generated_commands_compute ===
      PFN_vkGetPipelineIndirectMemoryRequirementsNV vkGetPipelineIndirectMemoryRequirementsNV = 0;
      PFN_vkCmdUpdatePipelineIndirectBufferNV       vkCmdUpdatePipelineIndirectBufferNV       = 0;
      PFN_vkGetPipelineIndirectDeviceAddressNV      vkGetPipelineIndirectDeviceAddressNV      = 0;

#if defined( VK_USE_PLATFORM_OHOS )
      //=== VK_OHOS_external_memory ===
      PFN_vkGetNativeBufferPropertiesOHOS vkGetNativeBufferPropertiesOHOS = 0;
      PFN_vkGetMemoryNativeBufferOHOS     vkGetMemoryNativeBufferOHOS     = 0;
#else
      PFN_dummy vkGetNativeBufferPropertiesOHOS_placeholder = 0;
      PFN_dummy vkGetMemoryNativeBufferOHOS_placeholder     = 0;
#endif /*VK_USE_PLATFORM_OHOS*/

      //=== VK_EXT_extended_dynamic_state3 ===
      PFN_vkCmdSetDepthClampEnableEXT                 vkCmdSetDepthClampEnableEXT                 = 0;
      PFN_vkCmdSetPolygonModeEXT                      vkCmdSetPolygonModeEXT                      = 0;
      PFN_vkCmdSetRasterizationSamplesEXT             vkCmdSetRasterizationSamplesEXT             = 0;
      PFN_vkCmdSetSampleMaskEXT                       vkCmdSetSampleMaskEXT                       = 0;
      PFN_vkCmdSetAlphaToCoverageEnableEXT            vkCmdSetAlphaToCoverageEnableEXT            = 0;
      PFN_vkCmdSetAlphaToOneEnableEXT                 vkCmdSetAlphaToOneEnableEXT                 = 0;
      PFN_vkCmdSetLogicOpEnableEXT                    vkCmdSetLogicOpEnableEXT                    = 0;
      PFN_vkCmdSetColorBlendEnableEXT                 vkCmdSetColorBlendEnableEXT                 = 0;
      PFN_vkCmdSetColorBlendEquationEXT               vkCmdSetColorBlendEquationEXT               = 0;
      PFN_vkCmdSetColorWriteMaskEXT                   vkCmdSetColorWriteMaskEXT                   = 0;
      PFN_vkCmdSetTessellationDomainOriginEXT         vkCmdSetTessellationDomainOriginEXT         = 0;
      PFN_vkCmdSetRasterizationStreamEXT              vkCmdSetRasterizationStreamEXT              = 0;
      PFN_vkCmdSetConservativeRasterizationModeEXT    vkCmdSetConservativeRasterizationModeEXT    = 0;
      PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT vkCmdSetExtraPrimitiveOverestimationSizeEXT = 0;
      PFN_vkCmdSetDepthClipEnableEXT                  vkCmdSetDepthClipEnableEXT                  = 0;
      PFN_vkCmdSetSampleLocationsEnableEXT            vkCmdSetSampleLocationsEnableEXT            = 0;
      PFN_vkCmdSetColorBlendAdvancedEXT               vkCmdSetColorBlendAdvancedEXT               = 0;
      PFN_vkCmdSetProvokingVertexModeEXT              vkCmdSetProvokingVertexModeEXT              = 0;
      PFN_vkCmdSetLineRasterizationModeEXT            vkCmdSetLineRasterizationModeEXT            = 0;
      PFN_vkCmdSetLineStippleEnableEXT                vkCmdSetLineStippleEnableEXT                = 0;
      PFN_vkCmdSetDepthClipNegativeOneToOneEXT        vkCmdSetDepthClipNegativeOneToOneEXT        = 0;
      PFN_vkCmdSetViewportWScalingEnableNV            vkCmdSetViewportWScalingEnableNV            = 0;
      PFN_vkCmdSetViewportSwizzleNV                   vkCmdSetViewportSwizzleNV                   = 0;
      PFN_vkCmdSetCoverageToColorEnableNV             vkCmdSetCoverageToColorEnableNV             = 0;
      PFN_vkCmdSetCoverageToColorLocationNV           vkCmdSetCoverageToColorLocationNV           = 0;
      PFN_vkCmdSetCoverageModulationModeNV            vkCmdSetCoverageModulationModeNV            = 0;
      PFN_vkCmdSetCoverageModulationTableEnableNV     vkCmdSetCoverageModulationTableEnableNV     = 0;
      PFN_vkCmdSetCoverageModulationTableNV           vkCmdSetCoverageModulationTableNV           = 0;
      PFN_vkCmdSetShadingRateImageEnableNV            vkCmdSetShadingRateImageEnableNV            = 0;
      PFN_vkCmdSetRepresentativeFragmentTestEnableNV  vkCmdSetRepresentativeFragmentTestEnableNV  = 0;
      PFN_vkCmdSetCoverageReductionModeNV             vkCmdSetCoverageReductionModeNV             = 0;

      //=== VK_ARM_tensors ===
      PFN_vkCreateTensorARM                              vkCreateTensorARM                              = 0;
      PFN_vkDestroyTensorARM                             vkDestroyTensorARM                             = 0;
      PFN_vkCreateTensorViewARM                          vkCreateTensorViewARM                          = 0;
      PFN_vkDestroyTensorViewARM                         vkDestroyTensorViewARM                         = 0;
      PFN_vkGetTensorMemoryRequirementsARM               vkGetTensorMemoryRequirementsARM               = 0;
      PFN_vkBindTensorMemoryARM                          vkBindTensorMemoryARM                          = 0;
      PFN_vkGetDeviceTensorMemoryRequirementsARM         vkGetDeviceTensorMemoryRequirementsARM         = 0;
      PFN_vkCmdCopyTensorARM                             vkCmdCopyTensorARM                             = 0;
      PFN_vkGetPhysicalDeviceExternalTensorPropertiesARM vkGetPhysicalDeviceExternalTensorPropertiesARM = 0;
      PFN_vkGetTensorOpaqueCaptureDescriptorDataARM      vkGetTensorOpaqueCaptureDescriptorDataARM      = 0;
      PFN_vkGetTensorViewOpaqueCaptureDescriptorDataARM  vkGetTensorViewOpaqueCaptureDescriptorDataARM  = 0;

      //=== VK_EXT_shader_module_identifier ===
      PFN_vkGetShaderModuleIdentifierEXT           vkGetShaderModuleIdentifierEXT           = 0;
      PFN_vkGetShaderModuleCreateInfoIdentifierEXT vkGetShaderModuleCreateInfoIdentifierEXT = 0;

      //=== VK_NV_optical_flow ===
      PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV vkGetPhysicalDeviceOpticalFlowImageFormatsNV = 0;
      PFN_vkCreateOpticalFlowSessionNV                 vkCreateOpticalFlowSessionNV                 = 0;
      PFN_vkDestroyOpticalFlowSessionNV                vkDestroyOpticalFlowSessionNV                = 0;
      PFN_vkBindOpticalFlowSessionImageNV              vkBindOpticalFlowSessionImageNV              = 0;
      PFN_vkCmdOpticalFlowExecuteNV                    vkCmdOpticalFlowExecuteNV                    = 0;

      //=== VK_KHR_maintenance5 ===
      PFN_vkCmdBindIndexBuffer2KHR             vkCmdBindIndexBuffer2KHR             = 0;
      PFN_vkGetRenderingAreaGranularityKHR     vkGetRenderingAreaGranularityKHR     = 0;
      PFN_vkGetDeviceImageSubresourceLayoutKHR vkGetDeviceImageSubresourceLayoutKHR = 0;
      PFN_vkGetImageSubresourceLayout2KHR      vkGetImageSubresourceLayout2KHR      = 0;

      //=== VK_AMD_anti_lag ===
      PFN_vkAntiLagUpdateAMD vkAntiLagUpdateAMD = 0;

      //=== VK_KHR_present_wait2 ===
      PFN_vkWaitForPresent2KHR vkWaitForPresent2KHR = 0;

      //=== VK_EXT_shader_object ===
      PFN_vkCreateShadersEXT         vkCreateShadersEXT         = 0;
      PFN_vkDestroyShaderEXT         vkDestroyShaderEXT         = 0;
      PFN_vkGetShaderBinaryDataEXT   vkGetShaderBinaryDataEXT   = 0;
      PFN_vkCmdBindShadersEXT        vkCmdBindShadersEXT        = 0;
      PFN_vkCmdSetDepthClampRangeEXT vkCmdSetDepthClampRangeEXT = 0;

      //=== VK_KHR_pipeline_binary ===
      PFN_vkCreatePipelineBinariesKHR      vkCreatePipelineBinariesKHR      = 0;
      PFN_vkDestroyPipelineBinaryKHR       vkDestroyPipelineBinaryKHR       = 0;
      PFN_vkGetPipelineKeyKHR              vkGetPipelineKeyKHR              = 0;
      PFN_vkGetPipelineBinaryDataKHR       vkGetPipelineBinaryDataKHR       = 0;
      PFN_vkReleaseCapturedPipelineDataKHR vkReleaseCapturedPipelineDataKHR = 0;

      //=== VK_QCOM_tile_properties ===
      PFN_vkGetFramebufferTilePropertiesQCOM      vkGetFramebufferTilePropertiesQCOM      = 0;
      PFN_vkGetDynamicRenderingTilePropertiesQCOM vkGetDynamicRenderingTilePropertiesQCOM = 0;

      //=== VK_KHR_swapchain_maintenance1 ===
      PFN_vkReleaseSwapchainImagesKHR vkReleaseSwapchainImagesKHR = 0;

      //=== VK_NV_cooperative_vector ===
      PFN_vkGetPhysicalDeviceCooperativeVectorPropertiesNV vkGetPhysicalDeviceCooperativeVectorPropertiesNV = 0;
      PFN_vkConvertCooperativeVectorMatrixNV               vkConvertCooperativeVectorMatrixNV               = 0;
      PFN_vkCmdConvertCooperativeVectorMatrixNV            vkCmdConvertCooperativeVectorMatrixNV            = 0;

      //=== VK_NV_low_latency2 ===
      PFN_vkSetLatencySleepModeNV  vkSetLatencySleepModeNV  = 0;
      PFN_vkLatencySleepNV         vkLatencySleepNV         = 0;
      PFN_vkSetLatencyMarkerNV     vkSetLatencyMarkerNV     = 0;
      PFN_vkGetLatencyTimingsNV    vkGetLatencyTimingsNV    = 0;
      PFN_vkQueueNotifyOutOfBandNV vkQueueNotifyOutOfBandNV = 0;

      //=== VK_KHR_cooperative_matrix ===
      PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR = 0;

      //=== VK_ARM_data_graph ===
      PFN_vkCreateDataGraphPipelinesARM                                        vkCreateDataGraphPipelinesARM                                        = 0;
      PFN_vkCreateDataGraphPipelineSessionARM                                  vkCreateDataGraphPipelineSessionARM                                  = 0;
      PFN_vkGetDataGraphPipelineSessionBindPointRequirementsARM                vkGetDataGraphPipelineSessionBindPointRequirementsARM                = 0;
      PFN_vkGetDataGraphPipelineSessionMemoryRequirementsARM                   vkGetDataGraphPipelineSessionMemoryRequirementsARM                   = 0;
      PFN_vkBindDataGraphPipelineSessionMemoryARM                              vkBindDataGraphPipelineSessionMemoryARM                              = 0;
      PFN_vkDestroyDataGraphPipelineSessionARM                                 vkDestroyDataGraphPipelineSessionARM                                 = 0;
      PFN_vkCmdDispatchDataGraphARM                                            vkCmdDispatchDataGraphARM                                            = 0;
      PFN_vkGetDataGraphPipelineAvailablePropertiesARM                         vkGetDataGraphPipelineAvailablePropertiesARM                         = 0;
      PFN_vkGetDataGraphPipelinePropertiesARM                                  vkGetDataGraphPipelinePropertiesARM                                  = 0;
      PFN_vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM                 vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM                 = 0;
      PFN_vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM = 0;

      //=== VK_ARM_data_graph_instruction_set_tosa ===
      PFN_vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM = 0;

      //=== VK_EXT_attachment_feedback_loop_dynamic_state ===
      PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT vkCmdSetAttachmentFeedbackLoopEnableEXT = 0;

#if defined( VK_USE_PLATFORM_SCREEN_QNX )
      //=== VK_QNX_external_memory_screen_buffer ===
      PFN_vkGetScreenBufferPropertiesQNX vkGetScreenBufferPropertiesQNX = 0;
#else
      PFN_dummy vkGetScreenBufferPropertiesQNX_placeholder = 0;
#endif /*VK_USE_PLATFORM_SCREEN_QNX*/

      //=== VK_KHR_line_rasterization ===
      PFN_vkCmdSetLineStippleKHR vkCmdSetLineStippleKHR = 0;

      //=== VK_KHR_calibrated_timestamps ===
      PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR vkGetPhysicalDeviceCalibrateableTimeDomainsKHR = 0;
      PFN_vkGetCalibratedTimestampsKHR                   vkGetCalibratedTimestampsKHR                   = 0;

      //=== VK_KHR_maintenance6 ===
      PFN_vkCmdBindDescriptorSets2KHR                   vkCmdBindDescriptorSets2KHR                   = 0;
      PFN_vkCmdPushConstants2KHR                        vkCmdPushConstants2KHR                        = 0;
      PFN_vkCmdPushDescriptorSet2KHR                    vkCmdPushDescriptorSet2KHR                    = 0;
      PFN_vkCmdPushDescriptorSetWithTemplate2KHR        vkCmdPushDescriptorSetWithTemplate2KHR        = 0;
      PFN_vkCmdSetDescriptorBufferOffsets2EXT           vkCmdSetDescriptorBufferOffsets2EXT           = 0;
      PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT vkCmdBindDescriptorBufferEmbeddedSamplers2EXT = 0;

      //=== VK_QCOM_tile_memory_heap ===
      PFN_vkCmdBindTileMemoryQCOM vkCmdBindTileMemoryQCOM = 0;

      //=== VK_KHR_copy_memory_indirect ===
      PFN_vkCmdCopyMemoryIndirectKHR        vkCmdCopyMemoryIndirectKHR        = 0;
      PFN_vkCmdCopyMemoryToImageIndirectKHR vkCmdCopyMemoryToImageIndirectKHR = 0;

      //=== VK_EXT_memory_decompression ===
      PFN_vkCmdDecompressMemoryEXT              vkCmdDecompressMemoryEXT              = 0;
      PFN_vkCmdDecompressMemoryIndirectCountEXT vkCmdDecompressMemoryIndirectCountEXT = 0;

      //=== VK_NV_external_compute_queue ===
      PFN_vkCreateExternalComputeQueueNV  vkCreateExternalComputeQueueNV  = 0;
      PFN_vkDestroyExternalComputeQueueNV vkDestroyExternalComputeQueueNV = 0;
      PFN_vkGetExternalComputeQueueDataNV vkGetExternalComputeQueueDataNV = 0;

      //=== VK_NV_cluster_acceleration_structure ===
      PFN_vkGetClusterAccelerationStructureBuildSizesNV    vkGetClusterAccelerationStructureBuildSizesNV    = 0;
      PFN_vkCmdBuildClusterAccelerationStructureIndirectNV vkCmdBuildClusterAccelerationStructureIndirectNV = 0;

      //=== VK_NV_partitioned_acceleration_structure ===
      PFN_vkGetPartitionedAccelerationStructuresBuildSizesNV vkGetPartitionedAccelerationStructuresBuildSizesNV = 0;
      PFN_vkCmdBuildPartitionedAccelerationStructuresNV      vkCmdBuildPartitionedAccelerationStructuresNV      = 0;

      //=== VK_EXT_device_generated_commands ===
      PFN_vkGetGeneratedCommandsMemoryRequirementsEXT vkGetGeneratedCommandsMemoryRequirementsEXT = 0;
      PFN_vkCmdPreprocessGeneratedCommandsEXT         vkCmdPreprocessGeneratedCommandsEXT         = 0;
      PFN_vkCmdExecuteGeneratedCommandsEXT            vkCmdExecuteGeneratedCommandsEXT            = 0;
      PFN_vkCreateIndirectCommandsLayoutEXT           vkCreateIndirectCommandsLayoutEXT           = 0;
      PFN_vkDestroyIndirectCommandsLayoutEXT          vkDestroyIndirectCommandsLayoutEXT          = 0;
      PFN_vkCreateIndirectExecutionSetEXT             vkCreateIndirectExecutionSetEXT             = 0;
      PFN_vkDestroyIndirectExecutionSetEXT            vkDestroyIndirectExecutionSetEXT            = 0;
      PFN_vkUpdateIndirectExecutionSetPipelineEXT     vkUpdateIndirectExecutionSetPipelineEXT     = 0;
      PFN_vkUpdateIndirectExecutionSetShaderEXT       vkUpdateIndirectExecutionSetShaderEXT       = 0;

      //=== VK_KHR_device_fault ===
      PFN_vkGetDeviceFaultReportsKHR   vkGetDeviceFaultReportsKHR   = 0;
      PFN_vkGetDeviceFaultDebugInfoKHR vkGetDeviceFaultDebugInfoKHR = 0;

#if defined( VK_USE_PLATFORM_OHOS )
      //=== VK_OHOS_surface ===
      PFN_vkCreateSurfaceOHOS vkCreateSurfaceOHOS = 0;
#else
      PFN_dummy vkCreateSurfaceOHOS_placeholder = 0;
#endif /*VK_USE_PLATFORM_OHOS*/

      //=== VK_NV_cooperative_matrix2 ===
      PFN_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV = 0;

#if defined( VK_USE_PLATFORM_METAL_EXT )
      //=== VK_EXT_external_memory_metal ===
      PFN_vkGetMemoryMetalHandleEXT           vkGetMemoryMetalHandleEXT           = 0;
      PFN_vkGetMemoryMetalHandlePropertiesEXT vkGetMemoryMetalHandlePropertiesEXT = 0;
#else
      PFN_dummy vkGetMemoryMetalHandleEXT_placeholder           = 0;
      PFN_dummy vkGetMemoryMetalHandlePropertiesEXT_placeholder = 0;
#endif /*VK_USE_PLATFORM_METAL_EXT*/

      //=== VK_ARM_performance_counters_by_region ===
      PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM = 0;

      //=== VK_ARM_shader_instrumentation ===
      PFN_vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM = 0;
      PFN_vkCreateShaderInstrumentationARM                         vkCreateShaderInstrumentationARM                         = 0;
      PFN_vkDestroyShaderInstrumentationARM                        vkDestroyShaderInstrumentationARM                        = 0;
      PFN_vkCmdBeginShaderInstrumentationARM                       vkCmdBeginShaderInstrumentationARM                       = 0;
      PFN_vkCmdEndShaderInstrumentationARM                         vkCmdEndShaderInstrumentationARM                         = 0;
      PFN_vkGetShaderInstrumentationValuesARM                      vkGetShaderInstrumentationValuesARM                      = 0;
      PFN_vkClearShaderInstrumentationMetricsARM                   vkClearShaderInstrumentationMetricsARM                   = 0;

      //=== VK_EXT_fragment_density_map_offset ===
      PFN_vkCmdEndRendering2EXT vkCmdEndRendering2EXT = 0;

      //=== VK_EXT_custom_resolve ===
      PFN_vkCmdBeginCustomResolveEXT vkCmdBeginCustomResolveEXT = 0;

      //=== VK_KHR_maintenance10 ===
      PFN_vkCmdEndRendering2KHR vkCmdEndRendering2KHR = 0;

      //=== VK_ARM_data_graph_optical_flow ===
      PFN_vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM = 0;

      //=== VK_NV_compute_occupancy_priority ===
      PFN_vkCmdSetComputeOccupancyPriorityNV vkCmdSetComputeOccupancyPriorityNV = 0;

#if defined( VK_USE_PLATFORM_UBM_SEC )
      //=== VK_SEC_ubm_surface ===
      PFN_vkCreateUbmSurfaceSEC                        vkCreateUbmSurfaceSEC                        = 0;
      PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC vkGetPhysicalDeviceUbmPresentationSupportSEC = 0;
#else
      PFN_dummy vkCreateUbmSurfaceSEC_placeholder                        = 0;
      PFN_dummy vkGetPhysicalDeviceUbmPresentationSupportSEC_placeholder = 0;
#endif /*VK_USE_PLATFORM_UBM_SEC*/

      //=== VK_EXT_primitive_restart_index ===
      PFN_vkCmdSetPrimitiveRestartIndexEXT vkCmdSetPrimitiveRestartIndexEXT = 0;

    public:
      DispatchLoaderDynamic() VULKAN_HPP_NOEXCEPT                                    = default;
      DispatchLoaderDynamic( DispatchLoaderDynamic const & rhs ) VULKAN_HPP_NOEXCEPT = default;

      DispatchLoaderDynamic( PFN_vkGetInstanceProcAddr getInstanceProcAddr ) VULKAN_HPP_NOEXCEPT
      {
        init( getInstanceProcAddr );
      }

      // This interface does not require a linked vulkan library.
      DispatchLoaderDynamic( VkInstance                instance,
                             PFN_vkGetInstanceProcAddr getInstanceProcAddr,
                             VkDevice                  device            = {},
                             PFN_vkGetDeviceProcAddr   getDeviceProcAddr = nullptr ) VULKAN_HPP_NOEXCEPT
      {
        init( instance, getInstanceProcAddr, device, getDeviceProcAddr );
      }

      template <typename DynamicLoader
#if VULKAN_HPP_ENABLE_DYNAMIC_LOADER_TOOL
                = VULKAN_HPP_NAMESPACE::detail::DynamicLoader
#endif
                >
      void init()
      {
        static DynamicLoader dl;
        init( dl );
      }

      template <typename DynamicLoader>
      void init( DynamicLoader const & dl ) VULKAN_HPP_NOEXCEPT
      {
        PFN_vkGetInstanceProcAddr getInstanceProcAddr = dl.template getProcAddress<PFN_vkGetInstanceProcAddr>( "vkGetInstanceProcAddr" );
        init( getInstanceProcAddr );
      }

      void init( PFN_vkGetInstanceProcAddr getInstanceProcAddr ) VULKAN_HPP_NOEXCEPT
      {
        VULKAN_HPP_ASSERT( getInstanceProcAddr );

        vkGetInstanceProcAddr = getInstanceProcAddr;

        //=== VK_VERSION_1_0 ===
        vkCreateInstance = PFN_vkCreateInstance( vkGetInstanceProcAddr( NULL, "vkCreateInstance" ) );
        vkEnumerateInstanceExtensionProperties =
          PFN_vkEnumerateInstanceExtensionProperties( vkGetInstanceProcAddr( NULL, "vkEnumerateInstanceExtensionProperties" ) );
        vkEnumerateInstanceLayerProperties = PFN_vkEnumerateInstanceLayerProperties( vkGetInstanceProcAddr( NULL, "vkEnumerateInstanceLayerProperties" ) );

        //=== VK_VERSION_1_1 ===
        vkEnumerateInstanceVersion = PFN_vkEnumerateInstanceVersion( vkGetInstanceProcAddr( NULL, "vkEnumerateInstanceVersion" ) );
      }

      // This interface does not require a linked vulkan library.
      void init( VkInstance                instance,
                 PFN_vkGetInstanceProcAddr getInstanceProcAddr,
                 VkDevice                  device              = {},
                 PFN_vkGetDeviceProcAddr /*getDeviceProcAddr*/ = nullptr ) VULKAN_HPP_NOEXCEPT
      {
        VULKAN_HPP_ASSERT( instance && getInstanceProcAddr );
        vkGetInstanceProcAddr = getInstanceProcAddr;
        init( Instance( instance ) );
        if ( device )
        {
          init( Device( device ) );
        }
      }

      void init( Instance instanceCpp ) VULKAN_HPP_NOEXCEPT
      {
        VkInstance instance = static_cast<VkInstance>( instanceCpp );

        //=== VK_VERSION_1_0 ===
        vkDestroyInstance           = PFN_vkDestroyInstance( vkGetInstanceProcAddr( instance, "vkDestroyInstance" ) );
        vkEnumeratePhysicalDevices  = PFN_vkEnumeratePhysicalDevices( vkGetInstanceProcAddr( instance, "vkEnumeratePhysicalDevices" ) );
        vkGetPhysicalDeviceFeatures = PFN_vkGetPhysicalDeviceFeatures( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFeatures" ) );
        vkGetPhysicalDeviceFormatProperties =
          PFN_vkGetPhysicalDeviceFormatProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFormatProperties" ) );
        vkGetPhysicalDeviceImageFormatProperties =
          PFN_vkGetPhysicalDeviceImageFormatProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceImageFormatProperties" ) );
        vkGetPhysicalDeviceProperties = PFN_vkGetPhysicalDeviceProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceProperties" ) );
        vkGetPhysicalDeviceQueueFamilyProperties =
          PFN_vkGetPhysicalDeviceQueueFamilyProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyProperties" ) );
        vkGetPhysicalDeviceMemoryProperties =
          PFN_vkGetPhysicalDeviceMemoryProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceMemoryProperties" ) );
        vkGetDeviceProcAddr = PFN_vkGetDeviceProcAddr( vkGetInstanceProcAddr( instance, "vkGetDeviceProcAddr" ) );
        vkCreateDevice      = PFN_vkCreateDevice( vkGetInstanceProcAddr( instance, "vkCreateDevice" ) );
        vkDestroyDevice     = PFN_vkDestroyDevice( vkGetInstanceProcAddr( instance, "vkDestroyDevice" ) );
        vkEnumerateDeviceExtensionProperties =
          PFN_vkEnumerateDeviceExtensionProperties( vkGetInstanceProcAddr( instance, "vkEnumerateDeviceExtensionProperties" ) );
        vkEnumerateDeviceLayerProperties   = PFN_vkEnumerateDeviceLayerProperties( vkGetInstanceProcAddr( instance, "vkEnumerateDeviceLayerProperties" ) );
        vkGetDeviceQueue                   = PFN_vkGetDeviceQueue( vkGetInstanceProcAddr( instance, "vkGetDeviceQueue" ) );
        vkQueueSubmit                      = PFN_vkQueueSubmit( vkGetInstanceProcAddr( instance, "vkQueueSubmit" ) );
        vkQueueWaitIdle                    = PFN_vkQueueWaitIdle( vkGetInstanceProcAddr( instance, "vkQueueWaitIdle" ) );
        vkDeviceWaitIdle                   = PFN_vkDeviceWaitIdle( vkGetInstanceProcAddr( instance, "vkDeviceWaitIdle" ) );
        vkAllocateMemory                   = PFN_vkAllocateMemory( vkGetInstanceProcAddr( instance, "vkAllocateMemory" ) );
        vkFreeMemory                       = PFN_vkFreeMemory( vkGetInstanceProcAddr( instance, "vkFreeMemory" ) );
        vkMapMemory                        = PFN_vkMapMemory( vkGetInstanceProcAddr( instance, "vkMapMemory" ) );
        vkUnmapMemory                      = PFN_vkUnmapMemory( vkGetInstanceProcAddr( instance, "vkUnmapMemory" ) );
        vkFlushMappedMemoryRanges          = PFN_vkFlushMappedMemoryRanges( vkGetInstanceProcAddr( instance, "vkFlushMappedMemoryRanges" ) );
        vkInvalidateMappedMemoryRanges     = PFN_vkInvalidateMappedMemoryRanges( vkGetInstanceProcAddr( instance, "vkInvalidateMappedMemoryRanges" ) );
        vkGetDeviceMemoryCommitment        = PFN_vkGetDeviceMemoryCommitment( vkGetInstanceProcAddr( instance, "vkGetDeviceMemoryCommitment" ) );
        vkBindBufferMemory                 = PFN_vkBindBufferMemory( vkGetInstanceProcAddr( instance, "vkBindBufferMemory" ) );
        vkBindImageMemory                  = PFN_vkBindImageMemory( vkGetInstanceProcAddr( instance, "vkBindImageMemory" ) );
        vkGetBufferMemoryRequirements      = PFN_vkGetBufferMemoryRequirements( vkGetInstanceProcAddr( instance, "vkGetBufferMemoryRequirements" ) );
        vkGetImageMemoryRequirements       = PFN_vkGetImageMemoryRequirements( vkGetInstanceProcAddr( instance, "vkGetImageMemoryRequirements" ) );
        vkGetImageSparseMemoryRequirements = PFN_vkGetImageSparseMemoryRequirements( vkGetInstanceProcAddr( instance, "vkGetImageSparseMemoryRequirements" ) );
        vkGetPhysicalDeviceSparseImageFormatProperties =
          PFN_vkGetPhysicalDeviceSparseImageFormatProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSparseImageFormatProperties" ) );
        vkQueueBindSparse            = PFN_vkQueueBindSparse( vkGetInstanceProcAddr( instance, "vkQueueBindSparse" ) );
        vkCreateFence                = PFN_vkCreateFence( vkGetInstanceProcAddr( instance, "vkCreateFence" ) );
        vkDestroyFence               = PFN_vkDestroyFence( vkGetInstanceProcAddr( instance, "vkDestroyFence" ) );
        vkResetFences                = PFN_vkResetFences( vkGetInstanceProcAddr( instance, "vkResetFences" ) );
        vkGetFenceStatus             = PFN_vkGetFenceStatus( vkGetInstanceProcAddr( instance, "vkGetFenceStatus" ) );
        vkWaitForFences              = PFN_vkWaitForFences( vkGetInstanceProcAddr( instance, "vkWaitForFences" ) );
        vkCreateSemaphore            = PFN_vkCreateSemaphore( vkGetInstanceProcAddr( instance, "vkCreateSemaphore" ) );
        vkDestroySemaphore           = PFN_vkDestroySemaphore( vkGetInstanceProcAddr( instance, "vkDestroySemaphore" ) );
        vkCreateQueryPool            = PFN_vkCreateQueryPool( vkGetInstanceProcAddr( instance, "vkCreateQueryPool" ) );
        vkDestroyQueryPool           = PFN_vkDestroyQueryPool( vkGetInstanceProcAddr( instance, "vkDestroyQueryPool" ) );
        vkGetQueryPoolResults        = PFN_vkGetQueryPoolResults( vkGetInstanceProcAddr( instance, "vkGetQueryPoolResults" ) );
        vkCreateBuffer               = PFN_vkCreateBuffer( vkGetInstanceProcAddr( instance, "vkCreateBuffer" ) );
        vkDestroyBuffer              = PFN_vkDestroyBuffer( vkGetInstanceProcAddr( instance, "vkDestroyBuffer" ) );
        vkCreateImage                = PFN_vkCreateImage( vkGetInstanceProcAddr( instance, "vkCreateImage" ) );
        vkDestroyImage               = PFN_vkDestroyImage( vkGetInstanceProcAddr( instance, "vkDestroyImage" ) );
        vkGetImageSubresourceLayout  = PFN_vkGetImageSubresourceLayout( vkGetInstanceProcAddr( instance, "vkGetImageSubresourceLayout" ) );
        vkCreateImageView            = PFN_vkCreateImageView( vkGetInstanceProcAddr( instance, "vkCreateImageView" ) );
        vkDestroyImageView           = PFN_vkDestroyImageView( vkGetInstanceProcAddr( instance, "vkDestroyImageView" ) );
        vkCreateCommandPool          = PFN_vkCreateCommandPool( vkGetInstanceProcAddr( instance, "vkCreateCommandPool" ) );
        vkDestroyCommandPool         = PFN_vkDestroyCommandPool( vkGetInstanceProcAddr( instance, "vkDestroyCommandPool" ) );
        vkResetCommandPool           = PFN_vkResetCommandPool( vkGetInstanceProcAddr( instance, "vkResetCommandPool" ) );
        vkAllocateCommandBuffers     = PFN_vkAllocateCommandBuffers( vkGetInstanceProcAddr( instance, "vkAllocateCommandBuffers" ) );
        vkFreeCommandBuffers         = PFN_vkFreeCommandBuffers( vkGetInstanceProcAddr( instance, "vkFreeCommandBuffers" ) );
        vkBeginCommandBuffer         = PFN_vkBeginCommandBuffer( vkGetInstanceProcAddr( instance, "vkBeginCommandBuffer" ) );
        vkEndCommandBuffer           = PFN_vkEndCommandBuffer( vkGetInstanceProcAddr( instance, "vkEndCommandBuffer" ) );
        vkResetCommandBuffer         = PFN_vkResetCommandBuffer( vkGetInstanceProcAddr( instance, "vkResetCommandBuffer" ) );
        vkCmdCopyBuffer              = PFN_vkCmdCopyBuffer( vkGetInstanceProcAddr( instance, "vkCmdCopyBuffer" ) );
        vkCmdCopyImage               = PFN_vkCmdCopyImage( vkGetInstanceProcAddr( instance, "vkCmdCopyImage" ) );
        vkCmdCopyBufferToImage       = PFN_vkCmdCopyBufferToImage( vkGetInstanceProcAddr( instance, "vkCmdCopyBufferToImage" ) );
        vkCmdCopyImageToBuffer       = PFN_vkCmdCopyImageToBuffer( vkGetInstanceProcAddr( instance, "vkCmdCopyImageToBuffer" ) );
        vkCmdUpdateBuffer            = PFN_vkCmdUpdateBuffer( vkGetInstanceProcAddr( instance, "vkCmdUpdateBuffer" ) );
        vkCmdFillBuffer              = PFN_vkCmdFillBuffer( vkGetInstanceProcAddr( instance, "vkCmdFillBuffer" ) );
        vkCmdPipelineBarrier         = PFN_vkCmdPipelineBarrier( vkGetInstanceProcAddr( instance, "vkCmdPipelineBarrier" ) );
        vkCmdBeginQuery              = PFN_vkCmdBeginQuery( vkGetInstanceProcAddr( instance, "vkCmdBeginQuery" ) );
        vkCmdEndQuery                = PFN_vkCmdEndQuery( vkGetInstanceProcAddr( instance, "vkCmdEndQuery" ) );
        vkCmdResetQueryPool          = PFN_vkCmdResetQueryPool( vkGetInstanceProcAddr( instance, "vkCmdResetQueryPool" ) );
        vkCmdWriteTimestamp          = PFN_vkCmdWriteTimestamp( vkGetInstanceProcAddr( instance, "vkCmdWriteTimestamp" ) );
        vkCmdCopyQueryPoolResults    = PFN_vkCmdCopyQueryPoolResults( vkGetInstanceProcAddr( instance, "vkCmdCopyQueryPoolResults" ) );
        vkCmdExecuteCommands         = PFN_vkCmdExecuteCommands( vkGetInstanceProcAddr( instance, "vkCmdExecuteCommands" ) );
        vkCreateEvent                = PFN_vkCreateEvent( vkGetInstanceProcAddr( instance, "vkCreateEvent" ) );
        vkDestroyEvent               = PFN_vkDestroyEvent( vkGetInstanceProcAddr( instance, "vkDestroyEvent" ) );
        vkGetEventStatus             = PFN_vkGetEventStatus( vkGetInstanceProcAddr( instance, "vkGetEventStatus" ) );
        vkSetEvent                   = PFN_vkSetEvent( vkGetInstanceProcAddr( instance, "vkSetEvent" ) );
        vkResetEvent                 = PFN_vkResetEvent( vkGetInstanceProcAddr( instance, "vkResetEvent" ) );
        vkCreateBufferView           = PFN_vkCreateBufferView( vkGetInstanceProcAddr( instance, "vkCreateBufferView" ) );
        vkDestroyBufferView          = PFN_vkDestroyBufferView( vkGetInstanceProcAddr( instance, "vkDestroyBufferView" ) );
        vkCreateShaderModule         = PFN_vkCreateShaderModule( vkGetInstanceProcAddr( instance, "vkCreateShaderModule" ) );
        vkDestroyShaderModule        = PFN_vkDestroyShaderModule( vkGetInstanceProcAddr( instance, "vkDestroyShaderModule" ) );
        vkCreatePipelineCache        = PFN_vkCreatePipelineCache( vkGetInstanceProcAddr( instance, "vkCreatePipelineCache" ) );
        vkDestroyPipelineCache       = PFN_vkDestroyPipelineCache( vkGetInstanceProcAddr( instance, "vkDestroyPipelineCache" ) );
        vkGetPipelineCacheData       = PFN_vkGetPipelineCacheData( vkGetInstanceProcAddr( instance, "vkGetPipelineCacheData" ) );
        vkMergePipelineCaches        = PFN_vkMergePipelineCaches( vkGetInstanceProcAddr( instance, "vkMergePipelineCaches" ) );
        vkCreateComputePipelines     = PFN_vkCreateComputePipelines( vkGetInstanceProcAddr( instance, "vkCreateComputePipelines" ) );
        vkDestroyPipeline            = PFN_vkDestroyPipeline( vkGetInstanceProcAddr( instance, "vkDestroyPipeline" ) );
        vkCreatePipelineLayout       = PFN_vkCreatePipelineLayout( vkGetInstanceProcAddr( instance, "vkCreatePipelineLayout" ) );
        vkDestroyPipelineLayout      = PFN_vkDestroyPipelineLayout( vkGetInstanceProcAddr( instance, "vkDestroyPipelineLayout" ) );
        vkCreateSampler              = PFN_vkCreateSampler( vkGetInstanceProcAddr( instance, "vkCreateSampler" ) );
        vkDestroySampler             = PFN_vkDestroySampler( vkGetInstanceProcAddr( instance, "vkDestroySampler" ) );
        vkCreateDescriptorSetLayout  = PFN_vkCreateDescriptorSetLayout( vkGetInstanceProcAddr( instance, "vkCreateDescriptorSetLayout" ) );
        vkDestroyDescriptorSetLayout = PFN_vkDestroyDescriptorSetLayout( vkGetInstanceProcAddr( instance, "vkDestroyDescriptorSetLayout" ) );
        vkCreateDescriptorPool       = PFN_vkCreateDescriptorPool( vkGetInstanceProcAddr( instance, "vkCreateDescriptorPool" ) );
        vkDestroyDescriptorPool      = PFN_vkDestroyDescriptorPool( vkGetInstanceProcAddr( instance, "vkDestroyDescriptorPool" ) );
        vkResetDescriptorPool        = PFN_vkResetDescriptorPool( vkGetInstanceProcAddr( instance, "vkResetDescriptorPool" ) );
        vkAllocateDescriptorSets     = PFN_vkAllocateDescriptorSets( vkGetInstanceProcAddr( instance, "vkAllocateDescriptorSets" ) );
        vkFreeDescriptorSets         = PFN_vkFreeDescriptorSets( vkGetInstanceProcAddr( instance, "vkFreeDescriptorSets" ) );
        vkUpdateDescriptorSets       = PFN_vkUpdateDescriptorSets( vkGetInstanceProcAddr( instance, "vkUpdateDescriptorSets" ) );
        vkCmdBindPipeline            = PFN_vkCmdBindPipeline( vkGetInstanceProcAddr( instance, "vkCmdBindPipeline" ) );
        vkCmdBindDescriptorSets      = PFN_vkCmdBindDescriptorSets( vkGetInstanceProcAddr( instance, "vkCmdBindDescriptorSets" ) );
        vkCmdClearColorImage         = PFN_vkCmdClearColorImage( vkGetInstanceProcAddr( instance, "vkCmdClearColorImage" ) );
        vkCmdDispatch                = PFN_vkCmdDispatch( vkGetInstanceProcAddr( instance, "vkCmdDispatch" ) );
        vkCmdDispatchIndirect        = PFN_vkCmdDispatchIndirect( vkGetInstanceProcAddr( instance, "vkCmdDispatchIndirect" ) );
        vkCmdSetEvent                = PFN_vkCmdSetEvent( vkGetInstanceProcAddr( instance, "vkCmdSetEvent" ) );
        vkCmdResetEvent              = PFN_vkCmdResetEvent( vkGetInstanceProcAddr( instance, "vkCmdResetEvent" ) );
        vkCmdWaitEvents              = PFN_vkCmdWaitEvents( vkGetInstanceProcAddr( instance, "vkCmdWaitEvents" ) );
        vkCmdPushConstants           = PFN_vkCmdPushConstants( vkGetInstanceProcAddr( instance, "vkCmdPushConstants" ) );
        vkCreateGraphicsPipelines    = PFN_vkCreateGraphicsPipelines( vkGetInstanceProcAddr( instance, "vkCreateGraphicsPipelines" ) );
        vkCreateFramebuffer          = PFN_vkCreateFramebuffer( vkGetInstanceProcAddr( instance, "vkCreateFramebuffer" ) );
        vkDestroyFramebuffer         = PFN_vkDestroyFramebuffer( vkGetInstanceProcAddr( instance, "vkDestroyFramebuffer" ) );
        vkCreateRenderPass           = PFN_vkCreateRenderPass( vkGetInstanceProcAddr( instance, "vkCreateRenderPass" ) );
        vkDestroyRenderPass          = PFN_vkDestroyRenderPass( vkGetInstanceProcAddr( instance, "vkDestroyRenderPass" ) );
        vkGetRenderAreaGranularity   = PFN_vkGetRenderAreaGranularity( vkGetInstanceProcAddr( instance, "vkGetRenderAreaGranularity" ) );
        vkCmdSetViewport             = PFN_vkCmdSetViewport( vkGetInstanceProcAddr( instance, "vkCmdSetViewport" ) );
        vkCmdSetScissor              = PFN_vkCmdSetScissor( vkGetInstanceProcAddr( instance, "vkCmdSetScissor" ) );
        vkCmdSetLineWidth            = PFN_vkCmdSetLineWidth( vkGetInstanceProcAddr( instance, "vkCmdSetLineWidth" ) );
        vkCmdSetDepthBias            = PFN_vkCmdSetDepthBias( vkGetInstanceProcAddr( instance, "vkCmdSetDepthBias" ) );
        vkCmdSetBlendConstants       = PFN_vkCmdSetBlendConstants( vkGetInstanceProcAddr( instance, "vkCmdSetBlendConstants" ) );
        vkCmdSetDepthBounds          = PFN_vkCmdSetDepthBounds( vkGetInstanceProcAddr( instance, "vkCmdSetDepthBounds" ) );
        vkCmdSetStencilCompareMask   = PFN_vkCmdSetStencilCompareMask( vkGetInstanceProcAddr( instance, "vkCmdSetStencilCompareMask" ) );
        vkCmdSetStencilWriteMask     = PFN_vkCmdSetStencilWriteMask( vkGetInstanceProcAddr( instance, "vkCmdSetStencilWriteMask" ) );
        vkCmdSetStencilReference     = PFN_vkCmdSetStencilReference( vkGetInstanceProcAddr( instance, "vkCmdSetStencilReference" ) );
        vkCmdBindIndexBuffer         = PFN_vkCmdBindIndexBuffer( vkGetInstanceProcAddr( instance, "vkCmdBindIndexBuffer" ) );
        vkCmdBindVertexBuffers       = PFN_vkCmdBindVertexBuffers( vkGetInstanceProcAddr( instance, "vkCmdBindVertexBuffers" ) );
        vkCmdDraw                    = PFN_vkCmdDraw( vkGetInstanceProcAddr( instance, "vkCmdDraw" ) );
        vkCmdDrawIndexed             = PFN_vkCmdDrawIndexed( vkGetInstanceProcAddr( instance, "vkCmdDrawIndexed" ) );
        vkCmdDrawIndirect            = PFN_vkCmdDrawIndirect( vkGetInstanceProcAddr( instance, "vkCmdDrawIndirect" ) );
        vkCmdDrawIndexedIndirect     = PFN_vkCmdDrawIndexedIndirect( vkGetInstanceProcAddr( instance, "vkCmdDrawIndexedIndirect" ) );
        vkCmdBlitImage               = PFN_vkCmdBlitImage( vkGetInstanceProcAddr( instance, "vkCmdBlitImage" ) );
        vkCmdClearDepthStencilImage  = PFN_vkCmdClearDepthStencilImage( vkGetInstanceProcAddr( instance, "vkCmdClearDepthStencilImage" ) );
        vkCmdClearAttachments        = PFN_vkCmdClearAttachments( vkGetInstanceProcAddr( instance, "vkCmdClearAttachments" ) );
        vkCmdResolveImage            = PFN_vkCmdResolveImage( vkGetInstanceProcAddr( instance, "vkCmdResolveImage" ) );
        vkCmdBeginRenderPass         = PFN_vkCmdBeginRenderPass( vkGetInstanceProcAddr( instance, "vkCmdBeginRenderPass" ) );
        vkCmdNextSubpass             = PFN_vkCmdNextSubpass( vkGetInstanceProcAddr( instance, "vkCmdNextSubpass" ) );
        vkCmdEndRenderPass           = PFN_vkCmdEndRenderPass( vkGetInstanceProcAddr( instance, "vkCmdEndRenderPass" ) );

        //=== VK_VERSION_1_1 ===
        vkBindBufferMemory2                = PFN_vkBindBufferMemory2( vkGetInstanceProcAddr( instance, "vkBindBufferMemory2" ) );
        vkBindImageMemory2                 = PFN_vkBindImageMemory2( vkGetInstanceProcAddr( instance, "vkBindImageMemory2" ) );
        vkGetDeviceGroupPeerMemoryFeatures = PFN_vkGetDeviceGroupPeerMemoryFeatures( vkGetInstanceProcAddr( instance, "vkGetDeviceGroupPeerMemoryFeatures" ) );
        vkCmdSetDeviceMask                 = PFN_vkCmdSetDeviceMask( vkGetInstanceProcAddr( instance, "vkCmdSetDeviceMask" ) );
        vkEnumeratePhysicalDeviceGroups    = PFN_vkEnumeratePhysicalDeviceGroups( vkGetInstanceProcAddr( instance, "vkEnumeratePhysicalDeviceGroups" ) );
        vkGetImageMemoryRequirements2      = PFN_vkGetImageMemoryRequirements2( vkGetInstanceProcAddr( instance, "vkGetImageMemoryRequirements2" ) );
        vkGetBufferMemoryRequirements2     = PFN_vkGetBufferMemoryRequirements2( vkGetInstanceProcAddr( instance, "vkGetBufferMemoryRequirements2" ) );
        vkGetImageSparseMemoryRequirements2 =
          PFN_vkGetImageSparseMemoryRequirements2( vkGetInstanceProcAddr( instance, "vkGetImageSparseMemoryRequirements2" ) );
        vkGetPhysicalDeviceFeatures2   = PFN_vkGetPhysicalDeviceFeatures2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFeatures2" ) );
        vkGetPhysicalDeviceProperties2 = PFN_vkGetPhysicalDeviceProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceProperties2" ) );
        vkGetPhysicalDeviceFormatProperties2 =
          PFN_vkGetPhysicalDeviceFormatProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFormatProperties2" ) );
        vkGetPhysicalDeviceImageFormatProperties2 =
          PFN_vkGetPhysicalDeviceImageFormatProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceImageFormatProperties2" ) );
        vkGetPhysicalDeviceQueueFamilyProperties2 =
          PFN_vkGetPhysicalDeviceQueueFamilyProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyProperties2" ) );
        vkGetPhysicalDeviceMemoryProperties2 =
          PFN_vkGetPhysicalDeviceMemoryProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceMemoryProperties2" ) );
        vkGetPhysicalDeviceSparseImageFormatProperties2 =
          PFN_vkGetPhysicalDeviceSparseImageFormatProperties2( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSparseImageFormatProperties2" ) );
        vkTrimCommandPool = PFN_vkTrimCommandPool( vkGetInstanceProcAddr( instance, "vkTrimCommandPool" ) );
        vkGetDeviceQueue2 = PFN_vkGetDeviceQueue2( vkGetInstanceProcAddr( instance, "vkGetDeviceQueue2" ) );
        vkGetPhysicalDeviceExternalBufferProperties =
          PFN_vkGetPhysicalDeviceExternalBufferProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalBufferProperties" ) );
        vkGetPhysicalDeviceExternalFenceProperties =
          PFN_vkGetPhysicalDeviceExternalFenceProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalFenceProperties" ) );
        vkGetPhysicalDeviceExternalSemaphoreProperties =
          PFN_vkGetPhysicalDeviceExternalSemaphoreProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalSemaphoreProperties" ) );
        vkCmdDispatchBase                 = PFN_vkCmdDispatchBase( vkGetInstanceProcAddr( instance, "vkCmdDispatchBase" ) );
        vkCreateDescriptorUpdateTemplate  = PFN_vkCreateDescriptorUpdateTemplate( vkGetInstanceProcAddr( instance, "vkCreateDescriptorUpdateTemplate" ) );
        vkDestroyDescriptorUpdateTemplate = PFN_vkDestroyDescriptorUpdateTemplate( vkGetInstanceProcAddr( instance, "vkDestroyDescriptorUpdateTemplate" ) );
        vkUpdateDescriptorSetWithTemplate = PFN_vkUpdateDescriptorSetWithTemplate( vkGetInstanceProcAddr( instance, "vkUpdateDescriptorSetWithTemplate" ) );
        vkGetDescriptorSetLayoutSupport   = PFN_vkGetDescriptorSetLayoutSupport( vkGetInstanceProcAddr( instance, "vkGetDescriptorSetLayoutSupport" ) );
        vkCreateSamplerYcbcrConversion    = PFN_vkCreateSamplerYcbcrConversion( vkGetInstanceProcAddr( instance, "vkCreateSamplerYcbcrConversion" ) );
        vkDestroySamplerYcbcrConversion   = PFN_vkDestroySamplerYcbcrConversion( vkGetInstanceProcAddr( instance, "vkDestroySamplerYcbcrConversion" ) );

        //=== VK_VERSION_1_2 ===
        vkResetQueryPool                = PFN_vkResetQueryPool( vkGetInstanceProcAddr( instance, "vkResetQueryPool" ) );
        vkGetSemaphoreCounterValue      = PFN_vkGetSemaphoreCounterValue( vkGetInstanceProcAddr( instance, "vkGetSemaphoreCounterValue" ) );
        vkWaitSemaphores                = PFN_vkWaitSemaphores( vkGetInstanceProcAddr( instance, "vkWaitSemaphores" ) );
        vkSignalSemaphore               = PFN_vkSignalSemaphore( vkGetInstanceProcAddr( instance, "vkSignalSemaphore" ) );
        vkGetBufferDeviceAddress        = PFN_vkGetBufferDeviceAddress( vkGetInstanceProcAddr( instance, "vkGetBufferDeviceAddress" ) );
        vkGetBufferOpaqueCaptureAddress = PFN_vkGetBufferOpaqueCaptureAddress( vkGetInstanceProcAddr( instance, "vkGetBufferOpaqueCaptureAddress" ) );
        vkGetDeviceMemoryOpaqueCaptureAddress =
          PFN_vkGetDeviceMemoryOpaqueCaptureAddress( vkGetInstanceProcAddr( instance, "vkGetDeviceMemoryOpaqueCaptureAddress" ) );
        vkCmdDrawIndirectCount        = PFN_vkCmdDrawIndirectCount( vkGetInstanceProcAddr( instance, "vkCmdDrawIndirectCount" ) );
        vkCmdDrawIndexedIndirectCount = PFN_vkCmdDrawIndexedIndirectCount( vkGetInstanceProcAddr( instance, "vkCmdDrawIndexedIndirectCount" ) );
        vkCreateRenderPass2           = PFN_vkCreateRenderPass2( vkGetInstanceProcAddr( instance, "vkCreateRenderPass2" ) );
        vkCmdBeginRenderPass2         = PFN_vkCmdBeginRenderPass2( vkGetInstanceProcAddr( instance, "vkCmdBeginRenderPass2" ) );
        vkCmdNextSubpass2             = PFN_vkCmdNextSubpass2( vkGetInstanceProcAddr( instance, "vkCmdNextSubpass2" ) );
        vkCmdEndRenderPass2           = PFN_vkCmdEndRenderPass2( vkGetInstanceProcAddr( instance, "vkCmdEndRenderPass2" ) );

        //=== VK_VERSION_1_3 ===
        vkGetPhysicalDeviceToolProperties = PFN_vkGetPhysicalDeviceToolProperties( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceToolProperties" ) );
        vkCreatePrivateDataSlot           = PFN_vkCreatePrivateDataSlot( vkGetInstanceProcAddr( instance, "vkCreatePrivateDataSlot" ) );
        vkDestroyPrivateDataSlot          = PFN_vkDestroyPrivateDataSlot( vkGetInstanceProcAddr( instance, "vkDestroyPrivateDataSlot" ) );
        vkSetPrivateData                  = PFN_vkSetPrivateData( vkGetInstanceProcAddr( instance, "vkSetPrivateData" ) );
        vkGetPrivateData                  = PFN_vkGetPrivateData( vkGetInstanceProcAddr( instance, "vkGetPrivateData" ) );
        vkCmdPipelineBarrier2             = PFN_vkCmdPipelineBarrier2( vkGetInstanceProcAddr( instance, "vkCmdPipelineBarrier2" ) );
        vkCmdWriteTimestamp2              = PFN_vkCmdWriteTimestamp2( vkGetInstanceProcAddr( instance, "vkCmdWriteTimestamp2" ) );
        vkQueueSubmit2                    = PFN_vkQueueSubmit2( vkGetInstanceProcAddr( instance, "vkQueueSubmit2" ) );
        vkCmdCopyBuffer2                  = PFN_vkCmdCopyBuffer2( vkGetInstanceProcAddr( instance, "vkCmdCopyBuffer2" ) );
        vkCmdCopyImage2                   = PFN_vkCmdCopyImage2( vkGetInstanceProcAddr( instance, "vkCmdCopyImage2" ) );
        vkCmdCopyBufferToImage2           = PFN_vkCmdCopyBufferToImage2( vkGetInstanceProcAddr( instance, "vkCmdCopyBufferToImage2" ) );
        vkCmdCopyImageToBuffer2           = PFN_vkCmdCopyImageToBuffer2( vkGetInstanceProcAddr( instance, "vkCmdCopyImageToBuffer2" ) );
        vkGetDeviceBufferMemoryRequirements =
          PFN_vkGetDeviceBufferMemoryRequirements( vkGetInstanceProcAddr( instance, "vkGetDeviceBufferMemoryRequirements" ) );
        vkGetDeviceImageMemoryRequirements = PFN_vkGetDeviceImageMemoryRequirements( vkGetInstanceProcAddr( instance, "vkGetDeviceImageMemoryRequirements" ) );
        vkGetDeviceImageSparseMemoryRequirements =
          PFN_vkGetDeviceImageSparseMemoryRequirements( vkGetInstanceProcAddr( instance, "vkGetDeviceImageSparseMemoryRequirements" ) );
        vkCmdSetEvent2                  = PFN_vkCmdSetEvent2( vkGetInstanceProcAddr( instance, "vkCmdSetEvent2" ) );
        vkCmdResetEvent2                = PFN_vkCmdResetEvent2( vkGetInstanceProcAddr( instance, "vkCmdResetEvent2" ) );
        vkCmdWaitEvents2                = PFN_vkCmdWaitEvents2( vkGetInstanceProcAddr( instance, "vkCmdWaitEvents2" ) );
        vkCmdBlitImage2                 = PFN_vkCmdBlitImage2( vkGetInstanceProcAddr( instance, "vkCmdBlitImage2" ) );
        vkCmdResolveImage2              = PFN_vkCmdResolveImage2( vkGetInstanceProcAddr( instance, "vkCmdResolveImage2" ) );
        vkCmdBeginRendering             = PFN_vkCmdBeginRendering( vkGetInstanceProcAddr( instance, "vkCmdBeginRendering" ) );
        vkCmdEndRendering               = PFN_vkCmdEndRendering( vkGetInstanceProcAddr( instance, "vkCmdEndRendering" ) );
        vkCmdSetCullMode                = PFN_vkCmdSetCullMode( vkGetInstanceProcAddr( instance, "vkCmdSetCullMode" ) );
        vkCmdSetFrontFace               = PFN_vkCmdSetFrontFace( vkGetInstanceProcAddr( instance, "vkCmdSetFrontFace" ) );
        vkCmdSetPrimitiveTopology       = PFN_vkCmdSetPrimitiveTopology( vkGetInstanceProcAddr( instance, "vkCmdSetPrimitiveTopology" ) );
        vkCmdSetViewportWithCount       = PFN_vkCmdSetViewportWithCount( vkGetInstanceProcAddr( instance, "vkCmdSetViewportWithCount" ) );
        vkCmdSetScissorWithCount        = PFN_vkCmdSetScissorWithCount( vkGetInstanceProcAddr( instance, "vkCmdSetScissorWithCount" ) );
        vkCmdBindVertexBuffers2         = PFN_vkCmdBindVertexBuffers2( vkGetInstanceProcAddr( instance, "vkCmdBindVertexBuffers2" ) );
        vkCmdSetDepthTestEnable         = PFN_vkCmdSetDepthTestEnable( vkGetInstanceProcAddr( instance, "vkCmdSetDepthTestEnable" ) );
        vkCmdSetDepthWriteEnable        = PFN_vkCmdSetDepthWriteEnable( vkGetInstanceProcAddr( instance, "vkCmdSetDepthWriteEnable" ) );
        vkCmdSetDepthCompareOp          = PFN_vkCmdSetDepthCompareOp( vkGetInstanceProcAddr( instance, "vkCmdSetDepthCompareOp" ) );
        vkCmdSetDepthBoundsTestEnable   = PFN_vkCmdSetDepthBoundsTestEnable( vkGetInstanceProcAddr( instance, "vkCmdSetDepthBoundsTestEnable" ) );
        vkCmdSetStencilTestEnable       = PFN_vkCmdSetStencilTestEnable( vkGetInstanceProcAddr( instance, "vkCmdSetStencilTestEnable" ) );
        vkCmdSetStencilOp               = PFN_vkCmdSetStencilOp( vkGetInstanceProcAddr( instance, "vkCmdSetStencilOp" ) );
        vkCmdSetRasterizerDiscardEnable = PFN_vkCmdSetRasterizerDiscardEnable( vkGetInstanceProcAddr( instance, "vkCmdSetRasterizerDiscardEnable" ) );
        vkCmdSetDepthBiasEnable         = PFN_vkCmdSetDepthBiasEnable( vkGetInstanceProcAddr( instance, "vkCmdSetDepthBiasEnable" ) );
        vkCmdSetPrimitiveRestartEnable  = PFN_vkCmdSetPrimitiveRestartEnable( vkGetInstanceProcAddr( instance, "vkCmdSetPrimitiveRestartEnable" ) );

        //=== VK_VERSION_1_4 ===
        vkMapMemory2                       = PFN_vkMapMemory2( vkGetInstanceProcAddr( instance, "vkMapMemory2" ) );
        vkUnmapMemory2                     = PFN_vkUnmapMemory2( vkGetInstanceProcAddr( instance, "vkUnmapMemory2" ) );
        vkGetDeviceImageSubresourceLayout  = PFN_vkGetDeviceImageSubresourceLayout( vkGetInstanceProcAddr( instance, "vkGetDeviceImageSubresourceLayout" ) );
        vkGetImageSubresourceLayout2       = PFN_vkGetImageSubresourceLayout2( vkGetInstanceProcAddr( instance, "vkGetImageSubresourceLayout2" ) );
        vkCopyMemoryToImage                = PFN_vkCopyMemoryToImage( vkGetInstanceProcAddr( instance, "vkCopyMemoryToImage" ) );
        vkCopyImageToMemory                = PFN_vkCopyImageToMemory( vkGetInstanceProcAddr( instance, "vkCopyImageToMemory" ) );
        vkCopyImageToImage                 = PFN_vkCopyImageToImage( vkGetInstanceProcAddr( instance, "vkCopyImageToImage" ) );
        vkTransitionImageLayout            = PFN_vkTransitionImageLayout( vkGetInstanceProcAddr( instance, "vkTransitionImageLayout" ) );
        vkCmdPushDescriptorSet             = PFN_vkCmdPushDescriptorSet( vkGetInstanceProcAddr( instance, "vkCmdPushDescriptorSet" ) );
        vkCmdPushDescriptorSetWithTemplate = PFN_vkCmdPushDescriptorSetWithTemplate( vkGetInstanceProcAddr( instance, "vkCmdPushDescriptorSetWithTemplate" ) );
        vkCmdBindDescriptorSets2           = PFN_vkCmdBindDescriptorSets2( vkGetInstanceProcAddr( instance, "vkCmdBindDescriptorSets2" ) );
        vkCmdPushConstants2                = PFN_vkCmdPushConstants2( vkGetInstanceProcAddr( instance, "vkCmdPushConstants2" ) );
        vkCmdPushDescriptorSet2            = PFN_vkCmdPushDescriptorSet2( vkGetInstanceProcAddr( instance, "vkCmdPushDescriptorSet2" ) );
        vkCmdPushDescriptorSetWithTemplate2 =
          PFN_vkCmdPushDescriptorSetWithTemplate2( vkGetInstanceProcAddr( instance, "vkCmdPushDescriptorSetWithTemplate2" ) );
        vkCmdSetLineStipple           = PFN_vkCmdSetLineStipple( vkGetInstanceProcAddr( instance, "vkCmdSetLineStipple" ) );
        vkCmdBindIndexBuffer2         = PFN_vkCmdBindIndexBuffer2( vkGetInstanceProcAddr( instance, "vkCmdBindIndexBuffer2" ) );
        vkGetRenderingAreaGranularity = PFN_vkGetRenderingAreaGranularity( vkGetInstanceProcAddr( instance, "vkGetRenderingAreaGranularity" ) );
        vkCmdSetRenderingAttachmentLocations =
          PFN_vkCmdSetRenderingAttachmentLocations( vkGetInstanceProcAddr( instance, "vkCmdSetRenderingAttachmentLocations" ) );
        vkCmdSetRenderingInputAttachmentIndices =
          PFN_vkCmdSetRenderingInputAttachmentIndices( vkGetInstanceProcAddr( instance, "vkCmdSetRenderingInputAttachmentIndices" ) );

        //=== VK_KHR_surface ===
        vkDestroySurfaceKHR = PFN_vkDestroySurfaceKHR( vkGetInstanceProcAddr( instance, "vkDestroySurfaceKHR" ) );
        vkGetPhysicalDeviceSurfaceSupportKHR =
          PFN_vkGetPhysicalDeviceSurfaceSupportKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceSupportKHR" ) );
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR =
          PFN_vkGetPhysicalDeviceSurfaceCapabilitiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR" ) );
        vkGetPhysicalDeviceSurfaceFormatsKHR =
          PFN_vkGetPhysicalDeviceSurfaceFormatsKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceFormatsKHR" ) );
        vkGetPhysicalDeviceSurfacePresentModesKHR =
          PFN_vkGetPhysicalDeviceSurfacePresentModesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfacePresentModesKHR" ) );

        //=== VK_KHR_swapchain ===
        vkCreateSwapchainKHR    = PFN_vkCreateSwapchainKHR( vkGetInstanceProcAddr( instance, "vkCreateSwapchainKHR" ) );
        vkDestroySwapchainKHR   = PFN_vkDestroySwapchainKHR( vkGetInstanceProcAddr( instance, "vkDestroySwapchainKHR" ) );
        vkGetSwapchainImagesKHR = PFN_vkGetSwapchainImagesKHR( vkGetInstanceProcAddr( instance, "vkGetSwapchainImagesKHR" ) );
        vkAcquireNextImageKHR   = PFN_vkAcquireNextImageKHR( vkGetInstanceProcAddr( instance, "vkAcquireNextImageKHR" ) );
        vkQueuePresentKHR       = PFN_vkQueuePresentKHR( vkGetInstanceProcAddr( instance, "vkQueuePresentKHR" ) );
        vkGetDeviceGroupPresentCapabilitiesKHR =
          PFN_vkGetDeviceGroupPresentCapabilitiesKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceGroupPresentCapabilitiesKHR" ) );
        vkGetDeviceGroupSurfacePresentModesKHR =
          PFN_vkGetDeviceGroupSurfacePresentModesKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceGroupSurfacePresentModesKHR" ) );
        vkGetPhysicalDevicePresentRectanglesKHR =
          PFN_vkGetPhysicalDevicePresentRectanglesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDevicePresentRectanglesKHR" ) );
        vkAcquireNextImage2KHR = PFN_vkAcquireNextImage2KHR( vkGetInstanceProcAddr( instance, "vkAcquireNextImage2KHR" ) );

        //=== VK_KHR_display ===
        vkGetPhysicalDeviceDisplayPropertiesKHR =
          PFN_vkGetPhysicalDeviceDisplayPropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDisplayPropertiesKHR" ) );
        vkGetPhysicalDeviceDisplayPlanePropertiesKHR =
          PFN_vkGetPhysicalDeviceDisplayPlanePropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR" ) );
        vkGetDisplayPlaneSupportedDisplaysKHR =
          PFN_vkGetDisplayPlaneSupportedDisplaysKHR( vkGetInstanceProcAddr( instance, "vkGetDisplayPlaneSupportedDisplaysKHR" ) );
        vkGetDisplayModePropertiesKHR    = PFN_vkGetDisplayModePropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetDisplayModePropertiesKHR" ) );
        vkCreateDisplayModeKHR           = PFN_vkCreateDisplayModeKHR( vkGetInstanceProcAddr( instance, "vkCreateDisplayModeKHR" ) );
        vkGetDisplayPlaneCapabilitiesKHR = PFN_vkGetDisplayPlaneCapabilitiesKHR( vkGetInstanceProcAddr( instance, "vkGetDisplayPlaneCapabilitiesKHR" ) );
        vkCreateDisplayPlaneSurfaceKHR   = PFN_vkCreateDisplayPlaneSurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateDisplayPlaneSurfaceKHR" ) );

        //=== VK_KHR_display_swapchain ===
        vkCreateSharedSwapchainsKHR = PFN_vkCreateSharedSwapchainsKHR( vkGetInstanceProcAddr( instance, "vkCreateSharedSwapchainsKHR" ) );

#if defined( VK_USE_PLATFORM_XLIB_KHR )
        //=== VK_KHR_xlib_surface ===
        vkCreateXlibSurfaceKHR = PFN_vkCreateXlibSurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateXlibSurfaceKHR" ) );
        vkGetPhysicalDeviceXlibPresentationSupportKHR =
          PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR" ) );
#endif /*VK_USE_PLATFORM_XLIB_KHR*/

#if defined( VK_USE_PLATFORM_XCB_KHR )
        //=== VK_KHR_xcb_surface ===
        vkCreateXcbSurfaceKHR = PFN_vkCreateXcbSurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateXcbSurfaceKHR" ) );
        vkGetPhysicalDeviceXcbPresentationSupportKHR =
          PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR" ) );
#endif /*VK_USE_PLATFORM_XCB_KHR*/

#if defined( VK_USE_PLATFORM_WAYLAND_KHR )
        //=== VK_KHR_wayland_surface ===
        vkCreateWaylandSurfaceKHR = PFN_vkCreateWaylandSurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateWaylandSurfaceKHR" ) );
        vkGetPhysicalDeviceWaylandPresentationSupportKHR =
          PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR" ) );
#endif /*VK_USE_PLATFORM_WAYLAND_KHR*/

#if defined( VK_USE_PLATFORM_ANDROID_KHR )
        //=== VK_KHR_android_surface ===
        vkCreateAndroidSurfaceKHR = PFN_vkCreateAndroidSurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateAndroidSurfaceKHR" ) );
#endif /*VK_USE_PLATFORM_ANDROID_KHR*/

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_win32_surface ===
        vkCreateWin32SurfaceKHR = PFN_vkCreateWin32SurfaceKHR( vkGetInstanceProcAddr( instance, "vkCreateWin32SurfaceKHR" ) );
        vkGetPhysicalDeviceWin32PresentationSupportKHR =
          PFN_vkGetPhysicalDeviceWin32PresentationSupportKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceWin32PresentationSupportKHR" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_EXT_debug_report ===
        vkCreateDebugReportCallbackEXT  = PFN_vkCreateDebugReportCallbackEXT( vkGetInstanceProcAddr( instance, "vkCreateDebugReportCallbackEXT" ) );
        vkDestroyDebugReportCallbackEXT = PFN_vkDestroyDebugReportCallbackEXT( vkGetInstanceProcAddr( instance, "vkDestroyDebugReportCallbackEXT" ) );
        vkDebugReportMessageEXT         = PFN_vkDebugReportMessageEXT( vkGetInstanceProcAddr( instance, "vkDebugReportMessageEXT" ) );

        //=== VK_EXT_debug_marker ===
        vkDebugMarkerSetObjectTagEXT  = PFN_vkDebugMarkerSetObjectTagEXT( vkGetInstanceProcAddr( instance, "vkDebugMarkerSetObjectTagEXT" ) );
        vkDebugMarkerSetObjectNameEXT = PFN_vkDebugMarkerSetObjectNameEXT( vkGetInstanceProcAddr( instance, "vkDebugMarkerSetObjectNameEXT" ) );
        vkCmdDebugMarkerBeginEXT      = PFN_vkCmdDebugMarkerBeginEXT( vkGetInstanceProcAddr( instance, "vkCmdDebugMarkerBeginEXT" ) );
        vkCmdDebugMarkerEndEXT        = PFN_vkCmdDebugMarkerEndEXT( vkGetInstanceProcAddr( instance, "vkCmdDebugMarkerEndEXT" ) );
        vkCmdDebugMarkerInsertEXT     = PFN_vkCmdDebugMarkerInsertEXT( vkGetInstanceProcAddr( instance, "vkCmdDebugMarkerInsertEXT" ) );

        //=== VK_KHR_video_queue ===
        vkGetPhysicalDeviceVideoCapabilitiesKHR =
          PFN_vkGetPhysicalDeviceVideoCapabilitiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceVideoCapabilitiesKHR" ) );
        vkGetPhysicalDeviceVideoFormatPropertiesKHR =
          PFN_vkGetPhysicalDeviceVideoFormatPropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceVideoFormatPropertiesKHR" ) );
        vkCreateVideoSessionKHR  = PFN_vkCreateVideoSessionKHR( vkGetInstanceProcAddr( instance, "vkCreateVideoSessionKHR" ) );
        vkDestroyVideoSessionKHR = PFN_vkDestroyVideoSessionKHR( vkGetInstanceProcAddr( instance, "vkDestroyVideoSessionKHR" ) );
        vkGetVideoSessionMemoryRequirementsKHR =
          PFN_vkGetVideoSessionMemoryRequirementsKHR( vkGetInstanceProcAddr( instance, "vkGetVideoSessionMemoryRequirementsKHR" ) );
        vkBindVideoSessionMemoryKHR        = PFN_vkBindVideoSessionMemoryKHR( vkGetInstanceProcAddr( instance, "vkBindVideoSessionMemoryKHR" ) );
        vkCreateVideoSessionParametersKHR  = PFN_vkCreateVideoSessionParametersKHR( vkGetInstanceProcAddr( instance, "vkCreateVideoSessionParametersKHR" ) );
        vkUpdateVideoSessionParametersKHR  = PFN_vkUpdateVideoSessionParametersKHR( vkGetInstanceProcAddr( instance, "vkUpdateVideoSessionParametersKHR" ) );
        vkDestroyVideoSessionParametersKHR = PFN_vkDestroyVideoSessionParametersKHR( vkGetInstanceProcAddr( instance, "vkDestroyVideoSessionParametersKHR" ) );
        vkCmdBeginVideoCodingKHR           = PFN_vkCmdBeginVideoCodingKHR( vkGetInstanceProcAddr( instance, "vkCmdBeginVideoCodingKHR" ) );
        vkCmdEndVideoCodingKHR             = PFN_vkCmdEndVideoCodingKHR( vkGetInstanceProcAddr( instance, "vkCmdEndVideoCodingKHR" ) );
        vkCmdControlVideoCodingKHR         = PFN_vkCmdControlVideoCodingKHR( vkGetInstanceProcAddr( instance, "vkCmdControlVideoCodingKHR" ) );

        //=== VK_KHR_video_decode_queue ===
        vkCmdDecodeVideoKHR = PFN_vkCmdDecodeVideoKHR( vkGetInstanceProcAddr( instance, "vkCmdDecodeVideoKHR" ) );

        //=== VK_EXT_transform_feedback ===
        vkCmdBindTransformFeedbackBuffersEXT =
          PFN_vkCmdBindTransformFeedbackBuffersEXT( vkGetInstanceProcAddr( instance, "vkCmdBindTransformFeedbackBuffersEXT" ) );
        vkCmdBeginTransformFeedbackEXT = PFN_vkCmdBeginTransformFeedbackEXT( vkGetInstanceProcAddr( instance, "vkCmdBeginTransformFeedbackEXT" ) );
        vkCmdEndTransformFeedbackEXT   = PFN_vkCmdEndTransformFeedbackEXT( vkGetInstanceProcAddr( instance, "vkCmdEndTransformFeedbackEXT" ) );
        vkCmdBeginQueryIndexedEXT      = PFN_vkCmdBeginQueryIndexedEXT( vkGetInstanceProcAddr( instance, "vkCmdBeginQueryIndexedEXT" ) );
        vkCmdEndQueryIndexedEXT        = PFN_vkCmdEndQueryIndexedEXT( vkGetInstanceProcAddr( instance, "vkCmdEndQueryIndexedEXT" ) );
        vkCmdDrawIndirectByteCountEXT  = PFN_vkCmdDrawIndirectByteCountEXT( vkGetInstanceProcAddr( instance, "vkCmdDrawIndirectByteCountEXT" ) );

        //=== VK_NVX_binary_import ===
        vkCreateCuModuleNVX    = PFN_vkCreateCuModuleNVX( vkGetInstanceProcAddr( instance, "vkCreateCuModuleNVX" ) );
        vkCreateCuFunctionNVX  = PFN_vkCreateCuFunctionNVX( vkGetInstanceProcAddr( instance, "vkCreateCuFunctionNVX" ) );
        vkDestroyCuModuleNVX   = PFN_vkDestroyCuModuleNVX( vkGetInstanceProcAddr( instance, "vkDestroyCuModuleNVX" ) );
        vkDestroyCuFunctionNVX = PFN_vkDestroyCuFunctionNVX( vkGetInstanceProcAddr( instance, "vkDestroyCuFunctionNVX" ) );
        vkCmdCuLaunchKernelNVX = PFN_vkCmdCuLaunchKernelNVX( vkGetInstanceProcAddr( instance, "vkCmdCuLaunchKernelNVX" ) );

        //=== VK_NVX_image_view_handle ===
        vkGetImageViewHandleNVX   = PFN_vkGetImageViewHandleNVX( vkGetInstanceProcAddr( instance, "vkGetImageViewHandleNVX" ) );
        vkGetImageViewHandle64NVX = PFN_vkGetImageViewHandle64NVX( vkGetInstanceProcAddr( instance, "vkGetImageViewHandle64NVX" ) );
        vkGetImageViewAddressNVX  = PFN_vkGetImageViewAddressNVX( vkGetInstanceProcAddr( instance, "vkGetImageViewAddressNVX" ) );
        vkGetDeviceCombinedImageSamplerIndexNVX =
          PFN_vkGetDeviceCombinedImageSamplerIndexNVX( vkGetInstanceProcAddr( instance, "vkGetDeviceCombinedImageSamplerIndexNVX" ) );

        //=== VK_AMD_draw_indirect_count ===
        vkCmdDrawIndirectCountAMD = PFN_vkCmdDrawIndirectCountAMD( vkGetInstanceProcAddr( instance, "vkCmdDrawIndirectCountAMD" ) );
        if ( !vkCmdDrawIndirectCount )
          vkCmdDrawIndirectCount = vkCmdDrawIndirectCountAMD;
        vkCmdDrawIndexedIndirectCountAMD = PFN_vkCmdDrawIndexedIndirectCountAMD( vkGetInstanceProcAddr( instance, "vkCmdDrawIndexedIndirectCountAMD" ) );
        if ( !vkCmdDrawIndexedIndirectCount )
          vkCmdDrawIndexedIndirectCount = vkCmdDrawIndexedIndirectCountAMD;

        //=== VK_AMD_shader_info ===
        vkGetShaderInfoAMD = PFN_vkGetShaderInfoAMD( vkGetInstanceProcAddr( instance, "vkGetShaderInfoAMD" ) );

        //=== VK_KHR_dynamic_rendering ===
        vkCmdBeginRenderingKHR = PFN_vkCmdBeginRenderingKHR( vkGetInstanceProcAddr( instance, "vkCmdBeginRenderingKHR" ) );
        if ( !vkCmdBeginRendering )
          vkCmdBeginRendering = vkCmdBeginRenderingKHR;
        vkCmdEndRenderingKHR = PFN_vkCmdEndRenderingKHR( vkGetInstanceProcAddr( instance, "vkCmdEndRenderingKHR" ) );
        if ( !vkCmdEndRendering )
          vkCmdEndRendering = vkCmdEndRenderingKHR;

#if defined( VK_USE_PLATFORM_GGP )
        //=== VK_GGP_stream_descriptor_surface ===
        vkCreateStreamDescriptorSurfaceGGP = PFN_vkCreateStreamDescriptorSurfaceGGP( vkGetInstanceProcAddr( instance, "vkCreateStreamDescriptorSurfaceGGP" ) );
#endif /*VK_USE_PLATFORM_GGP*/

        //=== VK_NV_external_memory_capabilities ===
        vkGetPhysicalDeviceExternalImageFormatPropertiesNV =
          PFN_vkGetPhysicalDeviceExternalImageFormatPropertiesNV( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalImageFormatPropertiesNV" ) );

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_NV_external_memory_win32 ===
        vkGetMemoryWin32HandleNV = PFN_vkGetMemoryWin32HandleNV( vkGetInstanceProcAddr( instance, "vkGetMemoryWin32HandleNV" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_get_physical_device_properties2 ===
        vkGetPhysicalDeviceFeatures2KHR = PFN_vkGetPhysicalDeviceFeatures2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFeatures2KHR" ) );
        if ( !vkGetPhysicalDeviceFeatures2 )
          vkGetPhysicalDeviceFeatures2 = vkGetPhysicalDeviceFeatures2KHR;
        vkGetPhysicalDeviceProperties2KHR = PFN_vkGetPhysicalDeviceProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceProperties2 )
          vkGetPhysicalDeviceProperties2 = vkGetPhysicalDeviceProperties2KHR;
        vkGetPhysicalDeviceFormatProperties2KHR =
          PFN_vkGetPhysicalDeviceFormatProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFormatProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceFormatProperties2 )
          vkGetPhysicalDeviceFormatProperties2 = vkGetPhysicalDeviceFormatProperties2KHR;
        vkGetPhysicalDeviceImageFormatProperties2KHR =
          PFN_vkGetPhysicalDeviceImageFormatProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceImageFormatProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceImageFormatProperties2 )
          vkGetPhysicalDeviceImageFormatProperties2 = vkGetPhysicalDeviceImageFormatProperties2KHR;
        vkGetPhysicalDeviceQueueFamilyProperties2KHR =
          PFN_vkGetPhysicalDeviceQueueFamilyProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceQueueFamilyProperties2 )
          vkGetPhysicalDeviceQueueFamilyProperties2 = vkGetPhysicalDeviceQueueFamilyProperties2KHR;
        vkGetPhysicalDeviceMemoryProperties2KHR =
          PFN_vkGetPhysicalDeviceMemoryProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceMemoryProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceMemoryProperties2 )
          vkGetPhysicalDeviceMemoryProperties2 = vkGetPhysicalDeviceMemoryProperties2KHR;
        vkGetPhysicalDeviceSparseImageFormatProperties2KHR =
          PFN_vkGetPhysicalDeviceSparseImageFormatProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSparseImageFormatProperties2KHR" ) );
        if ( !vkGetPhysicalDeviceSparseImageFormatProperties2 )
          vkGetPhysicalDeviceSparseImageFormatProperties2 = vkGetPhysicalDeviceSparseImageFormatProperties2KHR;

        //=== VK_KHR_device_group ===
        vkGetDeviceGroupPeerMemoryFeaturesKHR =
          PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceGroupPeerMemoryFeaturesKHR" ) );
        if ( !vkGetDeviceGroupPeerMemoryFeatures )
          vkGetDeviceGroupPeerMemoryFeatures = vkGetDeviceGroupPeerMemoryFeaturesKHR;
        vkCmdSetDeviceMaskKHR = PFN_vkCmdSetDeviceMaskKHR( vkGetInstanceProcAddr( instance, "vkCmdSetDeviceMaskKHR" ) );
        if ( !vkCmdSetDeviceMask )
          vkCmdSetDeviceMask = vkCmdSetDeviceMaskKHR;
        vkCmdDispatchBaseKHR = PFN_vkCmdDispatchBaseKHR( vkGetInstanceProcAddr( instance, "vkCmdDispatchBaseKHR" ) );
        if ( !vkCmdDispatchBase )
          vkCmdDispatchBase = vkCmdDispatchBaseKHR;

#if defined( VK_USE_PLATFORM_VI_NN )
        //=== VK_NN_vi_surface ===
        vkCreateViSurfaceNN = PFN_vkCreateViSurfaceNN( vkGetInstanceProcAddr( instance, "vkCreateViSurfaceNN" ) );
#endif /*VK_USE_PLATFORM_VI_NN*/

        //=== VK_KHR_maintenance1 ===
        vkTrimCommandPoolKHR = PFN_vkTrimCommandPoolKHR( vkGetInstanceProcAddr( instance, "vkTrimCommandPoolKHR" ) );
        if ( !vkTrimCommandPool )
          vkTrimCommandPool = vkTrimCommandPoolKHR;

        //=== VK_KHR_device_group_creation ===
        vkEnumeratePhysicalDeviceGroupsKHR = PFN_vkEnumeratePhysicalDeviceGroupsKHR( vkGetInstanceProcAddr( instance, "vkEnumeratePhysicalDeviceGroupsKHR" ) );
        if ( !vkEnumeratePhysicalDeviceGroups )
          vkEnumeratePhysicalDeviceGroups = vkEnumeratePhysicalDeviceGroupsKHR;

        //=== VK_KHR_external_memory_capabilities ===
        vkGetPhysicalDeviceExternalBufferPropertiesKHR =
          PFN_vkGetPhysicalDeviceExternalBufferPropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalBufferPropertiesKHR" ) );
        if ( !vkGetPhysicalDeviceExternalBufferProperties )
          vkGetPhysicalDeviceExternalBufferProperties = vkGetPhysicalDeviceExternalBufferPropertiesKHR;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_external_memory_win32 ===
        vkGetMemoryWin32HandleKHR = PFN_vkGetMemoryWin32HandleKHR( vkGetInstanceProcAddr( instance, "vkGetMemoryWin32HandleKHR" ) );
        vkGetMemoryWin32HandlePropertiesKHR =
          PFN_vkGetMemoryWin32HandlePropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetMemoryWin32HandlePropertiesKHR" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_external_memory_fd ===
        vkGetMemoryFdKHR           = PFN_vkGetMemoryFdKHR( vkGetInstanceProcAddr( instance, "vkGetMemoryFdKHR" ) );
        vkGetMemoryFdPropertiesKHR = PFN_vkGetMemoryFdPropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetMemoryFdPropertiesKHR" ) );

        //=== VK_KHR_external_semaphore_capabilities ===
        vkGetPhysicalDeviceExternalSemaphorePropertiesKHR =
          PFN_vkGetPhysicalDeviceExternalSemaphorePropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalSemaphorePropertiesKHR" ) );
        if ( !vkGetPhysicalDeviceExternalSemaphoreProperties )
          vkGetPhysicalDeviceExternalSemaphoreProperties = vkGetPhysicalDeviceExternalSemaphorePropertiesKHR;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_external_semaphore_win32 ===
        vkImportSemaphoreWin32HandleKHR = PFN_vkImportSemaphoreWin32HandleKHR( vkGetInstanceProcAddr( instance, "vkImportSemaphoreWin32HandleKHR" ) );
        vkGetSemaphoreWin32HandleKHR    = PFN_vkGetSemaphoreWin32HandleKHR( vkGetInstanceProcAddr( instance, "vkGetSemaphoreWin32HandleKHR" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_external_semaphore_fd ===
        vkImportSemaphoreFdKHR = PFN_vkImportSemaphoreFdKHR( vkGetInstanceProcAddr( instance, "vkImportSemaphoreFdKHR" ) );
        vkGetSemaphoreFdKHR    = PFN_vkGetSemaphoreFdKHR( vkGetInstanceProcAddr( instance, "vkGetSemaphoreFdKHR" ) );

        //=== VK_KHR_push_descriptor ===
        vkCmdPushDescriptorSetKHR = PFN_vkCmdPushDescriptorSetKHR( vkGetInstanceProcAddr( instance, "vkCmdPushDescriptorSetKHR" ) );
        if ( !vkCmdPushDescriptorSet )
          vkCmdPushDescriptorSet = vkCmdPushDescriptorSetKHR;
        vkCmdPushDescriptorSetWithTemplateKHR =
          PFN_vkCmdPushDescriptorSetWithTemplateKHR( vkGetInstanceProcAddr( instance, "vkCmdPushDescriptorSetWithTemplateKHR" ) );
        if ( !vkCmdPushDescriptorSetWithTemplate )
          vkCmdPushDescriptorSetWithTemplate = vkCmdPushDescriptorSetWithTemplateKHR;

        //=== VK_EXT_conditional_rendering ===
        vkCmdBeginConditionalRenderingEXT = PFN_vkCmdBeginConditionalRenderingEXT( vkGetInstanceProcAddr( instance, "vkCmdBeginConditionalRenderingEXT" ) );
        vkCmdEndConditionalRenderingEXT   = PFN_vkCmdEndConditionalRenderingEXT( vkGetInstanceProcAddr( instance, "vkCmdEndConditionalRenderingEXT" ) );

        //=== VK_KHR_descriptor_update_template ===
        vkCreateDescriptorUpdateTemplateKHR =
          PFN_vkCreateDescriptorUpdateTemplateKHR( vkGetInstanceProcAddr( instance, "vkCreateDescriptorUpdateTemplateKHR" ) );
        if ( !vkCreateDescriptorUpdateTemplate )
          vkCreateDescriptorUpdateTemplate = vkCreateDescriptorUpdateTemplateKHR;
        vkDestroyDescriptorUpdateTemplateKHR =
          PFN_vkDestroyDescriptorUpdateTemplateKHR( vkGetInstanceProcAddr( instance, "vkDestroyDescriptorUpdateTemplateKHR" ) );
        if ( !vkDestroyDescriptorUpdateTemplate )
          vkDestroyDescriptorUpdateTemplate = vkDestroyDescriptorUpdateTemplateKHR;
        vkUpdateDescriptorSetWithTemplateKHR =
          PFN_vkUpdateDescriptorSetWithTemplateKHR( vkGetInstanceProcAddr( instance, "vkUpdateDescriptorSetWithTemplateKHR" ) );
        if ( !vkUpdateDescriptorSetWithTemplate )
          vkUpdateDescriptorSetWithTemplate = vkUpdateDescriptorSetWithTemplateKHR;

        //=== VK_NV_clip_space_w_scaling ===
        vkCmdSetViewportWScalingNV = PFN_vkCmdSetViewportWScalingNV( vkGetInstanceProcAddr( instance, "vkCmdSetViewportWScalingNV" ) );

        //=== VK_EXT_direct_mode_display ===
        vkReleaseDisplayEXT = PFN_vkReleaseDisplayEXT( vkGetInstanceProcAddr( instance, "vkReleaseDisplayEXT" ) );

#if defined( VK_USE_PLATFORM_XLIB_XRANDR_EXT )
        //=== VK_EXT_acquire_xlib_display ===
        vkAcquireXlibDisplayEXT    = PFN_vkAcquireXlibDisplayEXT( vkGetInstanceProcAddr( instance, "vkAcquireXlibDisplayEXT" ) );
        vkGetRandROutputDisplayEXT = PFN_vkGetRandROutputDisplayEXT( vkGetInstanceProcAddr( instance, "vkGetRandROutputDisplayEXT" ) );
#endif /*VK_USE_PLATFORM_XLIB_XRANDR_EXT*/

        //=== VK_EXT_display_surface_counter ===
        vkGetPhysicalDeviceSurfaceCapabilities2EXT =
          PFN_vkGetPhysicalDeviceSurfaceCapabilities2EXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceCapabilities2EXT" ) );

        //=== VK_EXT_display_control ===
        vkDisplayPowerControlEXT  = PFN_vkDisplayPowerControlEXT( vkGetInstanceProcAddr( instance, "vkDisplayPowerControlEXT" ) );
        vkRegisterDeviceEventEXT  = PFN_vkRegisterDeviceEventEXT( vkGetInstanceProcAddr( instance, "vkRegisterDeviceEventEXT" ) );
        vkRegisterDisplayEventEXT = PFN_vkRegisterDisplayEventEXT( vkGetInstanceProcAddr( instance, "vkRegisterDisplayEventEXT" ) );
        vkGetSwapchainCounterEXT  = PFN_vkGetSwapchainCounterEXT( vkGetInstanceProcAddr( instance, "vkGetSwapchainCounterEXT" ) );

        //=== VK_GOOGLE_display_timing ===
        vkGetRefreshCycleDurationGOOGLE   = PFN_vkGetRefreshCycleDurationGOOGLE( vkGetInstanceProcAddr( instance, "vkGetRefreshCycleDurationGOOGLE" ) );
        vkGetPastPresentationTimingGOOGLE = PFN_vkGetPastPresentationTimingGOOGLE( vkGetInstanceProcAddr( instance, "vkGetPastPresentationTimingGOOGLE" ) );

        //=== VK_EXT_discard_rectangles ===
        vkCmdSetDiscardRectangleEXT       = PFN_vkCmdSetDiscardRectangleEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDiscardRectangleEXT" ) );
        vkCmdSetDiscardRectangleEnableEXT = PFN_vkCmdSetDiscardRectangleEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDiscardRectangleEnableEXT" ) );
        vkCmdSetDiscardRectangleModeEXT   = PFN_vkCmdSetDiscardRectangleModeEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDiscardRectangleModeEXT" ) );

        //=== VK_EXT_hdr_metadata ===
        vkSetHdrMetadataEXT = PFN_vkSetHdrMetadataEXT( vkGetInstanceProcAddr( instance, "vkSetHdrMetadataEXT" ) );

        //=== VK_KHR_create_renderpass2 ===
        vkCreateRenderPass2KHR = PFN_vkCreateRenderPass2KHR( vkGetInstanceProcAddr( instance, "vkCreateRenderPass2KHR" ) );
        if ( !vkCreateRenderPass2 )
          vkCreateRenderPass2 = vkCreateRenderPass2KHR;
        vkCmdBeginRenderPass2KHR = PFN_vkCmdBeginRenderPass2KHR( vkGetInstanceProcAddr( instance, "vkCmdBeginRenderPass2KHR" ) );
        if ( !vkCmdBeginRenderPass2 )
          vkCmdBeginRenderPass2 = vkCmdBeginRenderPass2KHR;
        vkCmdNextSubpass2KHR = PFN_vkCmdNextSubpass2KHR( vkGetInstanceProcAddr( instance, "vkCmdNextSubpass2KHR" ) );
        if ( !vkCmdNextSubpass2 )
          vkCmdNextSubpass2 = vkCmdNextSubpass2KHR;
        vkCmdEndRenderPass2KHR = PFN_vkCmdEndRenderPass2KHR( vkGetInstanceProcAddr( instance, "vkCmdEndRenderPass2KHR" ) );
        if ( !vkCmdEndRenderPass2 )
          vkCmdEndRenderPass2 = vkCmdEndRenderPass2KHR;

        //=== VK_KHR_shared_presentable_image ===
        vkGetSwapchainStatusKHR = PFN_vkGetSwapchainStatusKHR( vkGetInstanceProcAddr( instance, "vkGetSwapchainStatusKHR" ) );

        //=== VK_KHR_external_fence_capabilities ===
        vkGetPhysicalDeviceExternalFencePropertiesKHR =
          PFN_vkGetPhysicalDeviceExternalFencePropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalFencePropertiesKHR" ) );
        if ( !vkGetPhysicalDeviceExternalFenceProperties )
          vkGetPhysicalDeviceExternalFenceProperties = vkGetPhysicalDeviceExternalFencePropertiesKHR;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_external_fence_win32 ===
        vkImportFenceWin32HandleKHR = PFN_vkImportFenceWin32HandleKHR( vkGetInstanceProcAddr( instance, "vkImportFenceWin32HandleKHR" ) );
        vkGetFenceWin32HandleKHR    = PFN_vkGetFenceWin32HandleKHR( vkGetInstanceProcAddr( instance, "vkGetFenceWin32HandleKHR" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_external_fence_fd ===
        vkImportFenceFdKHR = PFN_vkImportFenceFdKHR( vkGetInstanceProcAddr( instance, "vkImportFenceFdKHR" ) );
        vkGetFenceFdKHR    = PFN_vkGetFenceFdKHR( vkGetInstanceProcAddr( instance, "vkGetFenceFdKHR" ) );

        //=== VK_KHR_performance_query ===
        vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR = PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(
          vkGetInstanceProcAddr( instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR" ) );
        vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR = PFN_vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(
          vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR" ) );
        vkAcquireProfilingLockKHR = PFN_vkAcquireProfilingLockKHR( vkGetInstanceProcAddr( instance, "vkAcquireProfilingLockKHR" ) );
        vkReleaseProfilingLockKHR = PFN_vkReleaseProfilingLockKHR( vkGetInstanceProcAddr( instance, "vkReleaseProfilingLockKHR" ) );

        //=== VK_KHR_get_surface_capabilities2 ===
        vkGetPhysicalDeviceSurfaceCapabilities2KHR =
          PFN_vkGetPhysicalDeviceSurfaceCapabilities2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceCapabilities2KHR" ) );
        vkGetPhysicalDeviceSurfaceFormats2KHR =
          PFN_vkGetPhysicalDeviceSurfaceFormats2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfaceFormats2KHR" ) );

        //=== VK_KHR_get_display_properties2 ===
        vkGetPhysicalDeviceDisplayProperties2KHR =
          PFN_vkGetPhysicalDeviceDisplayProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDisplayProperties2KHR" ) );
        vkGetPhysicalDeviceDisplayPlaneProperties2KHR =
          PFN_vkGetPhysicalDeviceDisplayPlaneProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDisplayPlaneProperties2KHR" ) );
        vkGetDisplayModeProperties2KHR    = PFN_vkGetDisplayModeProperties2KHR( vkGetInstanceProcAddr( instance, "vkGetDisplayModeProperties2KHR" ) );
        vkGetDisplayPlaneCapabilities2KHR = PFN_vkGetDisplayPlaneCapabilities2KHR( vkGetInstanceProcAddr( instance, "vkGetDisplayPlaneCapabilities2KHR" ) );

#if defined( VK_USE_PLATFORM_IOS_MVK )
        //=== VK_MVK_ios_surface ===
        vkCreateIOSSurfaceMVK = PFN_vkCreateIOSSurfaceMVK( vkGetInstanceProcAddr( instance, "vkCreateIOSSurfaceMVK" ) );
#endif /*VK_USE_PLATFORM_IOS_MVK*/

#if defined( VK_USE_PLATFORM_MACOS_MVK )
        //=== VK_MVK_macos_surface ===
        vkCreateMacOSSurfaceMVK = PFN_vkCreateMacOSSurfaceMVK( vkGetInstanceProcAddr( instance, "vkCreateMacOSSurfaceMVK" ) );
#endif /*VK_USE_PLATFORM_MACOS_MVK*/

        //=== VK_EXT_debug_utils ===
        vkSetDebugUtilsObjectNameEXT    = PFN_vkSetDebugUtilsObjectNameEXT( vkGetInstanceProcAddr( instance, "vkSetDebugUtilsObjectNameEXT" ) );
        vkSetDebugUtilsObjectTagEXT     = PFN_vkSetDebugUtilsObjectTagEXT( vkGetInstanceProcAddr( instance, "vkSetDebugUtilsObjectTagEXT" ) );
        vkQueueBeginDebugUtilsLabelEXT  = PFN_vkQueueBeginDebugUtilsLabelEXT( vkGetInstanceProcAddr( instance, "vkQueueBeginDebugUtilsLabelEXT" ) );
        vkQueueEndDebugUtilsLabelEXT    = PFN_vkQueueEndDebugUtilsLabelEXT( vkGetInstanceProcAddr( instance, "vkQueueEndDebugUtilsLabelEXT" ) );
        vkQueueInsertDebugUtilsLabelEXT = PFN_vkQueueInsertDebugUtilsLabelEXT( vkGetInstanceProcAddr( instance, "vkQueueInsertDebugUtilsLabelEXT" ) );
        vkCmdBeginDebugUtilsLabelEXT    = PFN_vkCmdBeginDebugUtilsLabelEXT( vkGetInstanceProcAddr( instance, "vkCmdBeginDebugUtilsLabelEXT" ) );
        vkCmdEndDebugUtilsLabelEXT      = PFN_vkCmdEndDebugUtilsLabelEXT( vkGetInstanceProcAddr( instance, "vkCmdEndDebugUtilsLabelEXT" ) );
        vkCmdInsertDebugUtilsLabelEXT   = PFN_vkCmdInsertDebugUtilsLabelEXT( vkGetInstanceProcAddr( instance, "vkCmdInsertDebugUtilsLabelEXT" ) );
        vkCreateDebugUtilsMessengerEXT  = PFN_vkCreateDebugUtilsMessengerEXT( vkGetInstanceProcAddr( instance, "vkCreateDebugUtilsMessengerEXT" ) );
        vkDestroyDebugUtilsMessengerEXT = PFN_vkDestroyDebugUtilsMessengerEXT( vkGetInstanceProcAddr( instance, "vkDestroyDebugUtilsMessengerEXT" ) );
        vkSubmitDebugUtilsMessageEXT    = PFN_vkSubmitDebugUtilsMessageEXT( vkGetInstanceProcAddr( instance, "vkSubmitDebugUtilsMessageEXT" ) );

#if defined( VK_USE_PLATFORM_ANDROID_KHR )
        //=== VK_ANDROID_external_memory_android_hardware_buffer ===
        vkGetAndroidHardwareBufferPropertiesANDROID =
          PFN_vkGetAndroidHardwareBufferPropertiesANDROID( vkGetInstanceProcAddr( instance, "vkGetAndroidHardwareBufferPropertiesANDROID" ) );
        vkGetMemoryAndroidHardwareBufferANDROID =
          PFN_vkGetMemoryAndroidHardwareBufferANDROID( vkGetInstanceProcAddr( instance, "vkGetMemoryAndroidHardwareBufferANDROID" ) );
#endif /*VK_USE_PLATFORM_ANDROID_KHR*/

        //=== VK_AMD_gpa_interface ===
        vkCreateGpaSessionAMD         = PFN_vkCreateGpaSessionAMD( vkGetInstanceProcAddr( instance, "vkCreateGpaSessionAMD" ) );
        vkDestroyGpaSessionAMD        = PFN_vkDestroyGpaSessionAMD( vkGetInstanceProcAddr( instance, "vkDestroyGpaSessionAMD" ) );
        vkSetGpaDeviceClockModeAMD    = PFN_vkSetGpaDeviceClockModeAMD( vkGetInstanceProcAddr( instance, "vkSetGpaDeviceClockModeAMD" ) );
        vkGetGpaDeviceClockInfoAMD    = PFN_vkGetGpaDeviceClockInfoAMD( vkGetInstanceProcAddr( instance, "vkGetGpaDeviceClockInfoAMD" ) );
        vkCmdBeginGpaSessionAMD       = PFN_vkCmdBeginGpaSessionAMD( vkGetInstanceProcAddr( instance, "vkCmdBeginGpaSessionAMD" ) );
        vkCmdEndGpaSessionAMD         = PFN_vkCmdEndGpaSessionAMD( vkGetInstanceProcAddr( instance, "vkCmdEndGpaSessionAMD" ) );
        vkCmdBeginGpaSampleAMD        = PFN_vkCmdBeginGpaSampleAMD( vkGetInstanceProcAddr( instance, "vkCmdBeginGpaSampleAMD" ) );
        vkCmdEndGpaSampleAMD          = PFN_vkCmdEndGpaSampleAMD( vkGetInstanceProcAddr( instance, "vkCmdEndGpaSampleAMD" ) );
        vkGetGpaSessionStatusAMD      = PFN_vkGetGpaSessionStatusAMD( vkGetInstanceProcAddr( instance, "vkGetGpaSessionStatusAMD" ) );
        vkGetGpaSessionResultsAMD     = PFN_vkGetGpaSessionResultsAMD( vkGetInstanceProcAddr( instance, "vkGetGpaSessionResultsAMD" ) );
        vkResetGpaSessionAMD          = PFN_vkResetGpaSessionAMD( vkGetInstanceProcAddr( instance, "vkResetGpaSessionAMD" ) );
        vkCmdCopyGpaSessionResultsAMD = PFN_vkCmdCopyGpaSessionResultsAMD( vkGetInstanceProcAddr( instance, "vkCmdCopyGpaSessionResultsAMD" ) );

#if defined( VK_ENABLE_BETA_EXTENSIONS )
        //=== VK_AMDX_shader_enqueue ===
        vkCreateExecutionGraphPipelinesAMDX =
          PFN_vkCreateExecutionGraphPipelinesAMDX( vkGetInstanceProcAddr( instance, "vkCreateExecutionGraphPipelinesAMDX" ) );
        vkGetExecutionGraphPipelineScratchSizeAMDX =
          PFN_vkGetExecutionGraphPipelineScratchSizeAMDX( vkGetInstanceProcAddr( instance, "vkGetExecutionGraphPipelineScratchSizeAMDX" ) );
        vkGetExecutionGraphPipelineNodeIndexAMDX =
          PFN_vkGetExecutionGraphPipelineNodeIndexAMDX( vkGetInstanceProcAddr( instance, "vkGetExecutionGraphPipelineNodeIndexAMDX" ) );
        vkCmdInitializeGraphScratchMemoryAMDX =
          PFN_vkCmdInitializeGraphScratchMemoryAMDX( vkGetInstanceProcAddr( instance, "vkCmdInitializeGraphScratchMemoryAMDX" ) );
        vkCmdDispatchGraphAMDX         = PFN_vkCmdDispatchGraphAMDX( vkGetInstanceProcAddr( instance, "vkCmdDispatchGraphAMDX" ) );
        vkCmdDispatchGraphIndirectAMDX = PFN_vkCmdDispatchGraphIndirectAMDX( vkGetInstanceProcAddr( instance, "vkCmdDispatchGraphIndirectAMDX" ) );
        vkCmdDispatchGraphIndirectCountAMDX =
          PFN_vkCmdDispatchGraphIndirectCountAMDX( vkGetInstanceProcAddr( instance, "vkCmdDispatchGraphIndirectCountAMDX" ) );
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

        //=== VK_EXT_descriptor_heap ===
        vkWriteSamplerDescriptorsEXT   = PFN_vkWriteSamplerDescriptorsEXT( vkGetInstanceProcAddr( instance, "vkWriteSamplerDescriptorsEXT" ) );
        vkWriteResourceDescriptorsEXT  = PFN_vkWriteResourceDescriptorsEXT( vkGetInstanceProcAddr( instance, "vkWriteResourceDescriptorsEXT" ) );
        vkCmdBindSamplerHeapEXT        = PFN_vkCmdBindSamplerHeapEXT( vkGetInstanceProcAddr( instance, "vkCmdBindSamplerHeapEXT" ) );
        vkCmdBindResourceHeapEXT       = PFN_vkCmdBindResourceHeapEXT( vkGetInstanceProcAddr( instance, "vkCmdBindResourceHeapEXT" ) );
        vkCmdPushDataEXT               = PFN_vkCmdPushDataEXT( vkGetInstanceProcAddr( instance, "vkCmdPushDataEXT" ) );
        vkGetImageOpaqueCaptureDataEXT = PFN_vkGetImageOpaqueCaptureDataEXT( vkGetInstanceProcAddr( instance, "vkGetImageOpaqueCaptureDataEXT" ) );
        vkGetPhysicalDeviceDescriptorSizeEXT =
          PFN_vkGetPhysicalDeviceDescriptorSizeEXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDescriptorSizeEXT" ) );
        vkRegisterCustomBorderColorEXT   = PFN_vkRegisterCustomBorderColorEXT( vkGetInstanceProcAddr( instance, "vkRegisterCustomBorderColorEXT" ) );
        vkUnregisterCustomBorderColorEXT = PFN_vkUnregisterCustomBorderColorEXT( vkGetInstanceProcAddr( instance, "vkUnregisterCustomBorderColorEXT" ) );
        vkGetTensorOpaqueCaptureDataARM  = PFN_vkGetTensorOpaqueCaptureDataARM( vkGetInstanceProcAddr( instance, "vkGetTensorOpaqueCaptureDataARM" ) );

        //=== VK_EXT_sample_locations ===
        vkCmdSetSampleLocationsEXT = PFN_vkCmdSetSampleLocationsEXT( vkGetInstanceProcAddr( instance, "vkCmdSetSampleLocationsEXT" ) );
        vkGetPhysicalDeviceMultisamplePropertiesEXT =
          PFN_vkGetPhysicalDeviceMultisamplePropertiesEXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceMultisamplePropertiesEXT" ) );

        //=== VK_KHR_get_memory_requirements2 ===
        vkGetImageMemoryRequirements2KHR = PFN_vkGetImageMemoryRequirements2KHR( vkGetInstanceProcAddr( instance, "vkGetImageMemoryRequirements2KHR" ) );
        if ( !vkGetImageMemoryRequirements2 )
          vkGetImageMemoryRequirements2 = vkGetImageMemoryRequirements2KHR;
        vkGetBufferMemoryRequirements2KHR = PFN_vkGetBufferMemoryRequirements2KHR( vkGetInstanceProcAddr( instance, "vkGetBufferMemoryRequirements2KHR" ) );
        if ( !vkGetBufferMemoryRequirements2 )
          vkGetBufferMemoryRequirements2 = vkGetBufferMemoryRequirements2KHR;
        vkGetImageSparseMemoryRequirements2KHR =
          PFN_vkGetImageSparseMemoryRequirements2KHR( vkGetInstanceProcAddr( instance, "vkGetImageSparseMemoryRequirements2KHR" ) );
        if ( !vkGetImageSparseMemoryRequirements2 )
          vkGetImageSparseMemoryRequirements2 = vkGetImageSparseMemoryRequirements2KHR;

        //=== VK_KHR_acceleration_structure ===
        vkCreateAccelerationStructureKHR  = PFN_vkCreateAccelerationStructureKHR( vkGetInstanceProcAddr( instance, "vkCreateAccelerationStructureKHR" ) );
        vkDestroyAccelerationStructureKHR = PFN_vkDestroyAccelerationStructureKHR( vkGetInstanceProcAddr( instance, "vkDestroyAccelerationStructureKHR" ) );
        vkCmdBuildAccelerationStructuresKHR =
          PFN_vkCmdBuildAccelerationStructuresKHR( vkGetInstanceProcAddr( instance, "vkCmdBuildAccelerationStructuresKHR" ) );
        vkCmdBuildAccelerationStructuresIndirectKHR =
          PFN_vkCmdBuildAccelerationStructuresIndirectKHR( vkGetInstanceProcAddr( instance, "vkCmdBuildAccelerationStructuresIndirectKHR" ) );
        vkBuildAccelerationStructuresKHR = PFN_vkBuildAccelerationStructuresKHR( vkGetInstanceProcAddr( instance, "vkBuildAccelerationStructuresKHR" ) );
        vkCopyAccelerationStructureKHR   = PFN_vkCopyAccelerationStructureKHR( vkGetInstanceProcAddr( instance, "vkCopyAccelerationStructureKHR" ) );
        vkCopyAccelerationStructureToMemoryKHR =
          PFN_vkCopyAccelerationStructureToMemoryKHR( vkGetInstanceProcAddr( instance, "vkCopyAccelerationStructureToMemoryKHR" ) );
        vkCopyMemoryToAccelerationStructureKHR =
          PFN_vkCopyMemoryToAccelerationStructureKHR( vkGetInstanceProcAddr( instance, "vkCopyMemoryToAccelerationStructureKHR" ) );
        vkWriteAccelerationStructuresPropertiesKHR =
          PFN_vkWriteAccelerationStructuresPropertiesKHR( vkGetInstanceProcAddr( instance, "vkWriteAccelerationStructuresPropertiesKHR" ) );
        vkCmdCopyAccelerationStructureKHR = PFN_vkCmdCopyAccelerationStructureKHR( vkGetInstanceProcAddr( instance, "vkCmdCopyAccelerationStructureKHR" ) );
        vkCmdCopyAccelerationStructureToMemoryKHR =
          PFN_vkCmdCopyAccelerationStructureToMemoryKHR( vkGetInstanceProcAddr( instance, "vkCmdCopyAccelerationStructureToMemoryKHR" ) );
        vkCmdCopyMemoryToAccelerationStructureKHR =
          PFN_vkCmdCopyMemoryToAccelerationStructureKHR( vkGetInstanceProcAddr( instance, "vkCmdCopyMemoryToAccelerationStructureKHR" ) );
        vkGetAccelerationStructureDeviceAddressKHR =
          PFN_vkGetAccelerationStructureDeviceAddressKHR( vkGetInstanceProcAddr( instance, "vkGetAccelerationStructureDeviceAddressKHR" ) );
        vkCmdWriteAccelerationStructuresPropertiesKHR =
          PFN_vkCmdWriteAccelerationStructuresPropertiesKHR( vkGetInstanceProcAddr( instance, "vkCmdWriteAccelerationStructuresPropertiesKHR" ) );
        vkGetDeviceAccelerationStructureCompatibilityKHR =
          PFN_vkGetDeviceAccelerationStructureCompatibilityKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceAccelerationStructureCompatibilityKHR" ) );
        vkGetAccelerationStructureBuildSizesKHR =
          PFN_vkGetAccelerationStructureBuildSizesKHR( vkGetInstanceProcAddr( instance, "vkGetAccelerationStructureBuildSizesKHR" ) );

        //=== VK_KHR_ray_tracing_pipeline ===
        vkCmdTraceRaysKHR              = PFN_vkCmdTraceRaysKHR( vkGetInstanceProcAddr( instance, "vkCmdTraceRaysKHR" ) );
        vkCreateRayTracingPipelinesKHR = PFN_vkCreateRayTracingPipelinesKHR( vkGetInstanceProcAddr( instance, "vkCreateRayTracingPipelinesKHR" ) );
        vkGetRayTracingShaderGroupHandlesKHR =
          PFN_vkGetRayTracingShaderGroupHandlesKHR( vkGetInstanceProcAddr( instance, "vkGetRayTracingShaderGroupHandlesKHR" ) );
        vkGetRayTracingCaptureReplayShaderGroupHandlesKHR =
          PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR( vkGetInstanceProcAddr( instance, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR" ) );
        vkCmdTraceRaysIndirectKHR = PFN_vkCmdTraceRaysIndirectKHR( vkGetInstanceProcAddr( instance, "vkCmdTraceRaysIndirectKHR" ) );
        vkGetRayTracingShaderGroupStackSizeKHR =
          PFN_vkGetRayTracingShaderGroupStackSizeKHR( vkGetInstanceProcAddr( instance, "vkGetRayTracingShaderGroupStackSizeKHR" ) );
        vkCmdSetRayTracingPipelineStackSizeKHR =
          PFN_vkCmdSetRayTracingPipelineStackSizeKHR( vkGetInstanceProcAddr( instance, "vkCmdSetRayTracingPipelineStackSizeKHR" ) );

        //=== VK_KHR_sampler_ycbcr_conversion ===
        vkCreateSamplerYcbcrConversionKHR = PFN_vkCreateSamplerYcbcrConversionKHR( vkGetInstanceProcAddr( instance, "vkCreateSamplerYcbcrConversionKHR" ) );
        if ( !vkCreateSamplerYcbcrConversion )
          vkCreateSamplerYcbcrConversion = vkCreateSamplerYcbcrConversionKHR;
        vkDestroySamplerYcbcrConversionKHR = PFN_vkDestroySamplerYcbcrConversionKHR( vkGetInstanceProcAddr( instance, "vkDestroySamplerYcbcrConversionKHR" ) );
        if ( !vkDestroySamplerYcbcrConversion )
          vkDestroySamplerYcbcrConversion = vkDestroySamplerYcbcrConversionKHR;

        //=== VK_KHR_bind_memory2 ===
        vkBindBufferMemory2KHR = PFN_vkBindBufferMemory2KHR( vkGetInstanceProcAddr( instance, "vkBindBufferMemory2KHR" ) );
        if ( !vkBindBufferMemory2 )
          vkBindBufferMemory2 = vkBindBufferMemory2KHR;
        vkBindImageMemory2KHR = PFN_vkBindImageMemory2KHR( vkGetInstanceProcAddr( instance, "vkBindImageMemory2KHR" ) );
        if ( !vkBindImageMemory2 )
          vkBindImageMemory2 = vkBindImageMemory2KHR;

        //=== VK_EXT_image_drm_format_modifier ===
        vkGetImageDrmFormatModifierPropertiesEXT =
          PFN_vkGetImageDrmFormatModifierPropertiesEXT( vkGetInstanceProcAddr( instance, "vkGetImageDrmFormatModifierPropertiesEXT" ) );

        //=== VK_EXT_validation_cache ===
        vkCreateValidationCacheEXT  = PFN_vkCreateValidationCacheEXT( vkGetInstanceProcAddr( instance, "vkCreateValidationCacheEXT" ) );
        vkDestroyValidationCacheEXT = PFN_vkDestroyValidationCacheEXT( vkGetInstanceProcAddr( instance, "vkDestroyValidationCacheEXT" ) );
        vkMergeValidationCachesEXT  = PFN_vkMergeValidationCachesEXT( vkGetInstanceProcAddr( instance, "vkMergeValidationCachesEXT" ) );
        vkGetValidationCacheDataEXT = PFN_vkGetValidationCacheDataEXT( vkGetInstanceProcAddr( instance, "vkGetValidationCacheDataEXT" ) );

        //=== VK_NV_shading_rate_image ===
        vkCmdBindShadingRateImageNV = PFN_vkCmdBindShadingRateImageNV( vkGetInstanceProcAddr( instance, "vkCmdBindShadingRateImageNV" ) );
        vkCmdSetViewportShadingRatePaletteNV =
          PFN_vkCmdSetViewportShadingRatePaletteNV( vkGetInstanceProcAddr( instance, "vkCmdSetViewportShadingRatePaletteNV" ) );
        vkCmdSetCoarseSampleOrderNV = PFN_vkCmdSetCoarseSampleOrderNV( vkGetInstanceProcAddr( instance, "vkCmdSetCoarseSampleOrderNV" ) );

        //=== VK_NV_ray_tracing ===
        vkCreateAccelerationStructureNV  = PFN_vkCreateAccelerationStructureNV( vkGetInstanceProcAddr( instance, "vkCreateAccelerationStructureNV" ) );
        vkDestroyAccelerationStructureNV = PFN_vkDestroyAccelerationStructureNV( vkGetInstanceProcAddr( instance, "vkDestroyAccelerationStructureNV" ) );
        vkGetAccelerationStructureMemoryRequirementsNV =
          PFN_vkGetAccelerationStructureMemoryRequirementsNV( vkGetInstanceProcAddr( instance, "vkGetAccelerationStructureMemoryRequirementsNV" ) );
        vkBindAccelerationStructureMemoryNV =
          PFN_vkBindAccelerationStructureMemoryNV( vkGetInstanceProcAddr( instance, "vkBindAccelerationStructureMemoryNV" ) );
        vkCmdBuildAccelerationStructureNV = PFN_vkCmdBuildAccelerationStructureNV( vkGetInstanceProcAddr( instance, "vkCmdBuildAccelerationStructureNV" ) );
        vkCmdCopyAccelerationStructureNV  = PFN_vkCmdCopyAccelerationStructureNV( vkGetInstanceProcAddr( instance, "vkCmdCopyAccelerationStructureNV" ) );
        vkCmdTraceRaysNV                  = PFN_vkCmdTraceRaysNV( vkGetInstanceProcAddr( instance, "vkCmdTraceRaysNV" ) );
        vkCreateRayTracingPipelinesNV     = PFN_vkCreateRayTracingPipelinesNV( vkGetInstanceProcAddr( instance, "vkCreateRayTracingPipelinesNV" ) );
        vkGetRayTracingShaderGroupHandlesNV =
          PFN_vkGetRayTracingShaderGroupHandlesNV( vkGetInstanceProcAddr( instance, "vkGetRayTracingShaderGroupHandlesNV" ) );
        if ( !vkGetRayTracingShaderGroupHandlesKHR )
          vkGetRayTracingShaderGroupHandlesKHR = vkGetRayTracingShaderGroupHandlesNV;
        vkGetAccelerationStructureHandleNV = PFN_vkGetAccelerationStructureHandleNV( vkGetInstanceProcAddr( instance, "vkGetAccelerationStructureHandleNV" ) );
        vkCmdWriteAccelerationStructuresPropertiesNV =
          PFN_vkCmdWriteAccelerationStructuresPropertiesNV( vkGetInstanceProcAddr( instance, "vkCmdWriteAccelerationStructuresPropertiesNV" ) );
        vkCompileDeferredNV = PFN_vkCompileDeferredNV( vkGetInstanceProcAddr( instance, "vkCompileDeferredNV" ) );

        //=== VK_KHR_maintenance3 ===
        vkGetDescriptorSetLayoutSupportKHR = PFN_vkGetDescriptorSetLayoutSupportKHR( vkGetInstanceProcAddr( instance, "vkGetDescriptorSetLayoutSupportKHR" ) );
        if ( !vkGetDescriptorSetLayoutSupport )
          vkGetDescriptorSetLayoutSupport = vkGetDescriptorSetLayoutSupportKHR;

        //=== VK_KHR_draw_indirect_count ===
        vkCmdDrawIndirectCountKHR = PFN_vkCmdDrawIndirectCountKHR( vkGetInstanceProcAddr( instance, "vkCmdDrawIndirectCountKHR" ) );
        if ( !vkCmdDrawIndirectCount )
          vkCmdDrawIndirectCount = vkCmdDrawIndirectCountKHR;
        vkCmdDrawIndexedIndirectCountKHR = PFN_vkCmdDrawIndexedIndirectCountKHR( vkGetInstanceProcAddr( instance, "vkCmdDrawIndexedIndirectCountKHR" ) );
        if ( !vkCmdDrawIndexedIndirectCount )
          vkCmdDrawIndexedIndirectCount = vkCmdDrawIndexedIndirectCountKHR;

        //=== VK_EXT_external_memory_host ===
        vkGetMemoryHostPointerPropertiesEXT =
          PFN_vkGetMemoryHostPointerPropertiesEXT( vkGetInstanceProcAddr( instance, "vkGetMemoryHostPointerPropertiesEXT" ) );

        //=== VK_AMD_buffer_marker ===
        vkCmdWriteBufferMarkerAMD  = PFN_vkCmdWriteBufferMarkerAMD( vkGetInstanceProcAddr( instance, "vkCmdWriteBufferMarkerAMD" ) );
        vkCmdWriteBufferMarker2AMD = PFN_vkCmdWriteBufferMarker2AMD( vkGetInstanceProcAddr( instance, "vkCmdWriteBufferMarker2AMD" ) );

        //=== VK_EXT_calibrated_timestamps ===
        vkGetPhysicalDeviceCalibrateableTimeDomainsEXT =
          PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsEXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsEXT" ) );
        if ( !vkGetPhysicalDeviceCalibrateableTimeDomainsKHR )
          vkGetPhysicalDeviceCalibrateableTimeDomainsKHR = vkGetPhysicalDeviceCalibrateableTimeDomainsEXT;
        vkGetCalibratedTimestampsEXT = PFN_vkGetCalibratedTimestampsEXT( vkGetInstanceProcAddr( instance, "vkGetCalibratedTimestampsEXT" ) );
        if ( !vkGetCalibratedTimestampsKHR )
          vkGetCalibratedTimestampsKHR = vkGetCalibratedTimestampsEXT;

        //=== VK_NV_mesh_shader ===
        vkCmdDrawMeshTasksNV              = PFN_vkCmdDrawMeshTasksNV( vkGetInstanceProcAddr( instance, "vkCmdDrawMeshTasksNV" ) );
        vkCmdDrawMeshTasksIndirectNV      = PFN_vkCmdDrawMeshTasksIndirectNV( vkGetInstanceProcAddr( instance, "vkCmdDrawMeshTasksIndirectNV" ) );
        vkCmdDrawMeshTasksIndirectCountNV = PFN_vkCmdDrawMeshTasksIndirectCountNV( vkGetInstanceProcAddr( instance, "vkCmdDrawMeshTasksIndirectCountNV" ) );

        //=== VK_NV_scissor_exclusive ===
        vkCmdSetExclusiveScissorEnableNV = PFN_vkCmdSetExclusiveScissorEnableNV( vkGetInstanceProcAddr( instance, "vkCmdSetExclusiveScissorEnableNV" ) );
        vkCmdSetExclusiveScissorNV       = PFN_vkCmdSetExclusiveScissorNV( vkGetInstanceProcAddr( instance, "vkCmdSetExclusiveScissorNV" ) );

        //=== VK_NV_device_diagnostic_checkpoints ===
        vkCmdSetCheckpointNV        = PFN_vkCmdSetCheckpointNV( vkGetInstanceProcAddr( instance, "vkCmdSetCheckpointNV" ) );
        vkGetQueueCheckpointDataNV  = PFN_vkGetQueueCheckpointDataNV( vkGetInstanceProcAddr( instance, "vkGetQueueCheckpointDataNV" ) );
        vkGetQueueCheckpointData2NV = PFN_vkGetQueueCheckpointData2NV( vkGetInstanceProcAddr( instance, "vkGetQueueCheckpointData2NV" ) );

        //=== VK_KHR_timeline_semaphore ===
        vkGetSemaphoreCounterValueKHR = PFN_vkGetSemaphoreCounterValueKHR( vkGetInstanceProcAddr( instance, "vkGetSemaphoreCounterValueKHR" ) );
        if ( !vkGetSemaphoreCounterValue )
          vkGetSemaphoreCounterValue = vkGetSemaphoreCounterValueKHR;
        vkWaitSemaphoresKHR = PFN_vkWaitSemaphoresKHR( vkGetInstanceProcAddr( instance, "vkWaitSemaphoresKHR" ) );
        if ( !vkWaitSemaphores )
          vkWaitSemaphores = vkWaitSemaphoresKHR;
        vkSignalSemaphoreKHR = PFN_vkSignalSemaphoreKHR( vkGetInstanceProcAddr( instance, "vkSignalSemaphoreKHR" ) );
        if ( !vkSignalSemaphore )
          vkSignalSemaphore = vkSignalSemaphoreKHR;

        //=== VK_EXT_present_timing ===
        vkSetSwapchainPresentTimingQueueSizeEXT =
          PFN_vkSetSwapchainPresentTimingQueueSizeEXT( vkGetInstanceProcAddr( instance, "vkSetSwapchainPresentTimingQueueSizeEXT" ) );
        vkGetSwapchainTimingPropertiesEXT = PFN_vkGetSwapchainTimingPropertiesEXT( vkGetInstanceProcAddr( instance, "vkGetSwapchainTimingPropertiesEXT" ) );
        vkGetSwapchainTimeDomainPropertiesEXT =
          PFN_vkGetSwapchainTimeDomainPropertiesEXT( vkGetInstanceProcAddr( instance, "vkGetSwapchainTimeDomainPropertiesEXT" ) );
        vkGetPastPresentationTimingEXT = PFN_vkGetPastPresentationTimingEXT( vkGetInstanceProcAddr( instance, "vkGetPastPresentationTimingEXT" ) );

        //=== VK_INTEL_performance_query ===
        vkInitializePerformanceApiINTEL   = PFN_vkInitializePerformanceApiINTEL( vkGetInstanceProcAddr( instance, "vkInitializePerformanceApiINTEL" ) );
        vkUninitializePerformanceApiINTEL = PFN_vkUninitializePerformanceApiINTEL( vkGetInstanceProcAddr( instance, "vkUninitializePerformanceApiINTEL" ) );
        vkCmdSetPerformanceMarkerINTEL    = PFN_vkCmdSetPerformanceMarkerINTEL( vkGetInstanceProcAddr( instance, "vkCmdSetPerformanceMarkerINTEL" ) );
        vkCmdSetPerformanceStreamMarkerINTEL =
          PFN_vkCmdSetPerformanceStreamMarkerINTEL( vkGetInstanceProcAddr( instance, "vkCmdSetPerformanceStreamMarkerINTEL" ) );
        vkCmdSetPerformanceOverrideINTEL = PFN_vkCmdSetPerformanceOverrideINTEL( vkGetInstanceProcAddr( instance, "vkCmdSetPerformanceOverrideINTEL" ) );
        vkAcquirePerformanceConfigurationINTEL =
          PFN_vkAcquirePerformanceConfigurationINTEL( vkGetInstanceProcAddr( instance, "vkAcquirePerformanceConfigurationINTEL" ) );
        vkReleasePerformanceConfigurationINTEL =
          PFN_vkReleasePerformanceConfigurationINTEL( vkGetInstanceProcAddr( instance, "vkReleasePerformanceConfigurationINTEL" ) );
        vkQueueSetPerformanceConfigurationINTEL =
          PFN_vkQueueSetPerformanceConfigurationINTEL( vkGetInstanceProcAddr( instance, "vkQueueSetPerformanceConfigurationINTEL" ) );
        vkGetPerformanceParameterINTEL = PFN_vkGetPerformanceParameterINTEL( vkGetInstanceProcAddr( instance, "vkGetPerformanceParameterINTEL" ) );

        //=== VK_AMD_display_native_hdr ===
        vkSetLocalDimmingAMD = PFN_vkSetLocalDimmingAMD( vkGetInstanceProcAddr( instance, "vkSetLocalDimmingAMD" ) );

#if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_imagepipe_surface ===
        vkCreateImagePipeSurfaceFUCHSIA = PFN_vkCreateImagePipeSurfaceFUCHSIA( vkGetInstanceProcAddr( instance, "vkCreateImagePipeSurfaceFUCHSIA" ) );
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_METAL_EXT )
        //=== VK_EXT_metal_surface ===
        vkCreateMetalSurfaceEXT = PFN_vkCreateMetalSurfaceEXT( vkGetInstanceProcAddr( instance, "vkCreateMetalSurfaceEXT" ) );
#endif /*VK_USE_PLATFORM_METAL_EXT*/

        //=== VK_KHR_fragment_shading_rate ===
        vkGetPhysicalDeviceFragmentShadingRatesKHR =
          PFN_vkGetPhysicalDeviceFragmentShadingRatesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceFragmentShadingRatesKHR" ) );
        vkCmdSetFragmentShadingRateKHR = PFN_vkCmdSetFragmentShadingRateKHR( vkGetInstanceProcAddr( instance, "vkCmdSetFragmentShadingRateKHR" ) );

        //=== VK_KHR_dynamic_rendering_local_read ===
        vkCmdSetRenderingAttachmentLocationsKHR =
          PFN_vkCmdSetRenderingAttachmentLocationsKHR( vkGetInstanceProcAddr( instance, "vkCmdSetRenderingAttachmentLocationsKHR" ) );
        if ( !vkCmdSetRenderingAttachmentLocations )
          vkCmdSetRenderingAttachmentLocations = vkCmdSetRenderingAttachmentLocationsKHR;
        vkCmdSetRenderingInputAttachmentIndicesKHR =
          PFN_vkCmdSetRenderingInputAttachmentIndicesKHR( vkGetInstanceProcAddr( instance, "vkCmdSetRenderingInputAttachmentIndicesKHR" ) );
        if ( !vkCmdSetRenderingInputAttachmentIndices )
          vkCmdSetRenderingInputAttachmentIndices = vkCmdSetRenderingInputAttachmentIndicesKHR;

        //=== VK_EXT_buffer_device_address ===
        vkGetBufferDeviceAddressEXT = PFN_vkGetBufferDeviceAddressEXT( vkGetInstanceProcAddr( instance, "vkGetBufferDeviceAddressEXT" ) );
        if ( !vkGetBufferDeviceAddress )
          vkGetBufferDeviceAddress = vkGetBufferDeviceAddressEXT;

        //=== VK_EXT_tooling_info ===
        vkGetPhysicalDeviceToolPropertiesEXT =
          PFN_vkGetPhysicalDeviceToolPropertiesEXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceToolPropertiesEXT" ) );
        if ( !vkGetPhysicalDeviceToolProperties )
          vkGetPhysicalDeviceToolProperties = vkGetPhysicalDeviceToolPropertiesEXT;

        //=== VK_KHR_present_wait ===
        vkWaitForPresentKHR = PFN_vkWaitForPresentKHR( vkGetInstanceProcAddr( instance, "vkWaitForPresentKHR" ) );

        //=== VK_NV_cooperative_matrix ===
        vkGetPhysicalDeviceCooperativeMatrixPropertiesNV =
          PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesNV( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesNV" ) );

        //=== VK_NV_coverage_reduction_mode ===
        vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV = PFN_vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(
          vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV" ) );

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_EXT_full_screen_exclusive ===
        vkGetPhysicalDeviceSurfacePresentModes2EXT =
          PFN_vkGetPhysicalDeviceSurfacePresentModes2EXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceSurfacePresentModes2EXT" ) );
        vkAcquireFullScreenExclusiveModeEXT =
          PFN_vkAcquireFullScreenExclusiveModeEXT( vkGetInstanceProcAddr( instance, "vkAcquireFullScreenExclusiveModeEXT" ) );
        vkReleaseFullScreenExclusiveModeEXT =
          PFN_vkReleaseFullScreenExclusiveModeEXT( vkGetInstanceProcAddr( instance, "vkReleaseFullScreenExclusiveModeEXT" ) );
        vkGetDeviceGroupSurfacePresentModes2EXT =
          PFN_vkGetDeviceGroupSurfacePresentModes2EXT( vkGetInstanceProcAddr( instance, "vkGetDeviceGroupSurfacePresentModes2EXT" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_EXT_headless_surface ===
        vkCreateHeadlessSurfaceEXT = PFN_vkCreateHeadlessSurfaceEXT( vkGetInstanceProcAddr( instance, "vkCreateHeadlessSurfaceEXT" ) );

        //=== VK_KHR_buffer_device_address ===
        vkGetBufferDeviceAddressKHR = PFN_vkGetBufferDeviceAddressKHR( vkGetInstanceProcAddr( instance, "vkGetBufferDeviceAddressKHR" ) );
        if ( !vkGetBufferDeviceAddress )
          vkGetBufferDeviceAddress = vkGetBufferDeviceAddressKHR;
        vkGetBufferOpaqueCaptureAddressKHR = PFN_vkGetBufferOpaqueCaptureAddressKHR( vkGetInstanceProcAddr( instance, "vkGetBufferOpaqueCaptureAddressKHR" ) );
        if ( !vkGetBufferOpaqueCaptureAddress )
          vkGetBufferOpaqueCaptureAddress = vkGetBufferOpaqueCaptureAddressKHR;
        vkGetDeviceMemoryOpaqueCaptureAddressKHR =
          PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceMemoryOpaqueCaptureAddressKHR" ) );
        if ( !vkGetDeviceMemoryOpaqueCaptureAddress )
          vkGetDeviceMemoryOpaqueCaptureAddress = vkGetDeviceMemoryOpaqueCaptureAddressKHR;

        //=== VK_EXT_line_rasterization ===
        vkCmdSetLineStippleEXT = PFN_vkCmdSetLineStippleEXT( vkGetInstanceProcAddr( instance, "vkCmdSetLineStippleEXT" ) );
        if ( !vkCmdSetLineStipple )
          vkCmdSetLineStipple = vkCmdSetLineStippleEXT;

        //=== VK_EXT_host_query_reset ===
        vkResetQueryPoolEXT = PFN_vkResetQueryPoolEXT( vkGetInstanceProcAddr( instance, "vkResetQueryPoolEXT" ) );
        if ( !vkResetQueryPool )
          vkResetQueryPool = vkResetQueryPoolEXT;

        //=== VK_EXT_extended_dynamic_state ===
        vkCmdSetCullModeEXT = PFN_vkCmdSetCullModeEXT( vkGetInstanceProcAddr( instance, "vkCmdSetCullModeEXT" ) );
        if ( !vkCmdSetCullMode )
          vkCmdSetCullMode = vkCmdSetCullModeEXT;
        vkCmdSetFrontFaceEXT = PFN_vkCmdSetFrontFaceEXT( vkGetInstanceProcAddr( instance, "vkCmdSetFrontFaceEXT" ) );
        if ( !vkCmdSetFrontFace )
          vkCmdSetFrontFace = vkCmdSetFrontFaceEXT;
        vkCmdSetPrimitiveTopologyEXT = PFN_vkCmdSetPrimitiveTopologyEXT( vkGetInstanceProcAddr( instance, "vkCmdSetPrimitiveTopologyEXT" ) );
        if ( !vkCmdSetPrimitiveTopology )
          vkCmdSetPrimitiveTopology = vkCmdSetPrimitiveTopologyEXT;
        vkCmdSetViewportWithCountEXT = PFN_vkCmdSetViewportWithCountEXT( vkGetInstanceProcAddr( instance, "vkCmdSetViewportWithCountEXT" ) );
        if ( !vkCmdSetViewportWithCount )
          vkCmdSetViewportWithCount = vkCmdSetViewportWithCountEXT;
        vkCmdSetScissorWithCountEXT = PFN_vkCmdSetScissorWithCountEXT( vkGetInstanceProcAddr( instance, "vkCmdSetScissorWithCountEXT" ) );
        if ( !vkCmdSetScissorWithCount )
          vkCmdSetScissorWithCount = vkCmdSetScissorWithCountEXT;
        vkCmdBindVertexBuffers2EXT = PFN_vkCmdBindVertexBuffers2EXT( vkGetInstanceProcAddr( instance, "vkCmdBindVertexBuffers2EXT" ) );
        if ( !vkCmdBindVertexBuffers2 )
          vkCmdBindVertexBuffers2 = vkCmdBindVertexBuffers2EXT;
        vkCmdSetDepthTestEnableEXT = PFN_vkCmdSetDepthTestEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDepthTestEnableEXT" ) );
        if ( !vkCmdSetDepthTestEnable )
          vkCmdSetDepthTestEnable = vkCmdSetDepthTestEnableEXT;
        vkCmdSetDepthWriteEnableEXT = PFN_vkCmdSetDepthWriteEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDepthWriteEnableEXT" ) );
        if ( !vkCmdSetDepthWriteEnable )
          vkCmdSetDepthWriteEnable = vkCmdSetDepthWriteEnableEXT;
        vkCmdSetDepthCompareOpEXT = PFN_vkCmdSetDepthCompareOpEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDepthCompareOpEXT" ) );
        if ( !vkCmdSetDepthCompareOp )
          vkCmdSetDepthCompareOp = vkCmdSetDepthCompareOpEXT;
        vkCmdSetDepthBoundsTestEnableEXT = PFN_vkCmdSetDepthBoundsTestEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDepthBoundsTestEnableEXT" ) );
        if ( !vkCmdSetDepthBoundsTestEnable )
          vkCmdSetDepthBoundsTestEnable = vkCmdSetDepthBoundsTestEnableEXT;
        vkCmdSetStencilTestEnableEXT = PFN_vkCmdSetStencilTestEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetStencilTestEnableEXT" ) );
        if ( !vkCmdSetStencilTestEnable )
          vkCmdSetStencilTestEnable = vkCmdSetStencilTestEnableEXT;
        vkCmdSetStencilOpEXT = PFN_vkCmdSetStencilOpEXT( vkGetInstanceProcAddr( instance, "vkCmdSetStencilOpEXT" ) );
        if ( !vkCmdSetStencilOp )
          vkCmdSetStencilOp = vkCmdSetStencilOpEXT;

        //=== VK_KHR_deferred_host_operations ===
        vkCreateDeferredOperationKHR  = PFN_vkCreateDeferredOperationKHR( vkGetInstanceProcAddr( instance, "vkCreateDeferredOperationKHR" ) );
        vkDestroyDeferredOperationKHR = PFN_vkDestroyDeferredOperationKHR( vkGetInstanceProcAddr( instance, "vkDestroyDeferredOperationKHR" ) );
        vkGetDeferredOperationMaxConcurrencyKHR =
          PFN_vkGetDeferredOperationMaxConcurrencyKHR( vkGetInstanceProcAddr( instance, "vkGetDeferredOperationMaxConcurrencyKHR" ) );
        vkGetDeferredOperationResultKHR = PFN_vkGetDeferredOperationResultKHR( vkGetInstanceProcAddr( instance, "vkGetDeferredOperationResultKHR" ) );
        vkDeferredOperationJoinKHR      = PFN_vkDeferredOperationJoinKHR( vkGetInstanceProcAddr( instance, "vkDeferredOperationJoinKHR" ) );

        //=== VK_KHR_pipeline_executable_properties ===
        vkGetPipelineExecutablePropertiesKHR =
          PFN_vkGetPipelineExecutablePropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPipelineExecutablePropertiesKHR" ) );
        vkGetPipelineExecutableStatisticsKHR =
          PFN_vkGetPipelineExecutableStatisticsKHR( vkGetInstanceProcAddr( instance, "vkGetPipelineExecutableStatisticsKHR" ) );
        vkGetPipelineExecutableInternalRepresentationsKHR =
          PFN_vkGetPipelineExecutableInternalRepresentationsKHR( vkGetInstanceProcAddr( instance, "vkGetPipelineExecutableInternalRepresentationsKHR" ) );

        //=== VK_EXT_host_image_copy ===
        vkCopyMemoryToImageEXT = PFN_vkCopyMemoryToImageEXT( vkGetInstanceProcAddr( instance, "vkCopyMemoryToImageEXT" ) );
        if ( !vkCopyMemoryToImage )
          vkCopyMemoryToImage = vkCopyMemoryToImageEXT;
        vkCopyImageToMemoryEXT = PFN_vkCopyImageToMemoryEXT( vkGetInstanceProcAddr( instance, "vkCopyImageToMemoryEXT" ) );
        if ( !vkCopyImageToMemory )
          vkCopyImageToMemory = vkCopyImageToMemoryEXT;
        vkCopyImageToImageEXT = PFN_vkCopyImageToImageEXT( vkGetInstanceProcAddr( instance, "vkCopyImageToImageEXT" ) );
        if ( !vkCopyImageToImage )
          vkCopyImageToImage = vkCopyImageToImageEXT;
        vkTransitionImageLayoutEXT = PFN_vkTransitionImageLayoutEXT( vkGetInstanceProcAddr( instance, "vkTransitionImageLayoutEXT" ) );
        if ( !vkTransitionImageLayout )
          vkTransitionImageLayout = vkTransitionImageLayoutEXT;
        vkGetImageSubresourceLayout2EXT = PFN_vkGetImageSubresourceLayout2EXT( vkGetInstanceProcAddr( instance, "vkGetImageSubresourceLayout2EXT" ) );
        if ( !vkGetImageSubresourceLayout2 )
          vkGetImageSubresourceLayout2 = vkGetImageSubresourceLayout2EXT;

        //=== VK_KHR_map_memory2 ===
        vkMapMemory2KHR = PFN_vkMapMemory2KHR( vkGetInstanceProcAddr( instance, "vkMapMemory2KHR" ) );
        if ( !vkMapMemory2 )
          vkMapMemory2 = vkMapMemory2KHR;
        vkUnmapMemory2KHR = PFN_vkUnmapMemory2KHR( vkGetInstanceProcAddr( instance, "vkUnmapMemory2KHR" ) );
        if ( !vkUnmapMemory2 )
          vkUnmapMemory2 = vkUnmapMemory2KHR;

        //=== VK_EXT_swapchain_maintenance1 ===
        vkReleaseSwapchainImagesEXT = PFN_vkReleaseSwapchainImagesEXT( vkGetInstanceProcAddr( instance, "vkReleaseSwapchainImagesEXT" ) );
        if ( !vkReleaseSwapchainImagesKHR )
          vkReleaseSwapchainImagesKHR = vkReleaseSwapchainImagesEXT;

        //=== VK_NV_device_generated_commands ===
        vkGetGeneratedCommandsMemoryRequirementsNV =
          PFN_vkGetGeneratedCommandsMemoryRequirementsNV( vkGetInstanceProcAddr( instance, "vkGetGeneratedCommandsMemoryRequirementsNV" ) );
        vkCmdPreprocessGeneratedCommandsNV = PFN_vkCmdPreprocessGeneratedCommandsNV( vkGetInstanceProcAddr( instance, "vkCmdPreprocessGeneratedCommandsNV" ) );
        vkCmdExecuteGeneratedCommandsNV    = PFN_vkCmdExecuteGeneratedCommandsNV( vkGetInstanceProcAddr( instance, "vkCmdExecuteGeneratedCommandsNV" ) );
        vkCmdBindPipelineShaderGroupNV     = PFN_vkCmdBindPipelineShaderGroupNV( vkGetInstanceProcAddr( instance, "vkCmdBindPipelineShaderGroupNV" ) );
        vkCreateIndirectCommandsLayoutNV   = PFN_vkCreateIndirectCommandsLayoutNV( vkGetInstanceProcAddr( instance, "vkCreateIndirectCommandsLayoutNV" ) );
        vkDestroyIndirectCommandsLayoutNV  = PFN_vkDestroyIndirectCommandsLayoutNV( vkGetInstanceProcAddr( instance, "vkDestroyIndirectCommandsLayoutNV" ) );

        //=== VK_EXT_depth_bias_control ===
        vkCmdSetDepthBias2EXT = PFN_vkCmdSetDepthBias2EXT( vkGetInstanceProcAddr( instance, "vkCmdSetDepthBias2EXT" ) );

        //=== VK_EXT_acquire_drm_display ===
        vkAcquireDrmDisplayEXT = PFN_vkAcquireDrmDisplayEXT( vkGetInstanceProcAddr( instance, "vkAcquireDrmDisplayEXT" ) );
        vkGetDrmDisplayEXT     = PFN_vkGetDrmDisplayEXT( vkGetInstanceProcAddr( instance, "vkGetDrmDisplayEXT" ) );

        //=== VK_EXT_private_data ===
        vkCreatePrivateDataSlotEXT = PFN_vkCreatePrivateDataSlotEXT( vkGetInstanceProcAddr( instance, "vkCreatePrivateDataSlotEXT" ) );
        if ( !vkCreatePrivateDataSlot )
          vkCreatePrivateDataSlot = vkCreatePrivateDataSlotEXT;
        vkDestroyPrivateDataSlotEXT = PFN_vkDestroyPrivateDataSlotEXT( vkGetInstanceProcAddr( instance, "vkDestroyPrivateDataSlotEXT" ) );
        if ( !vkDestroyPrivateDataSlot )
          vkDestroyPrivateDataSlot = vkDestroyPrivateDataSlotEXT;
        vkSetPrivateDataEXT = PFN_vkSetPrivateDataEXT( vkGetInstanceProcAddr( instance, "vkSetPrivateDataEXT" ) );
        if ( !vkSetPrivateData )
          vkSetPrivateData = vkSetPrivateDataEXT;
        vkGetPrivateDataEXT = PFN_vkGetPrivateDataEXT( vkGetInstanceProcAddr( instance, "vkGetPrivateDataEXT" ) );
        if ( !vkGetPrivateData )
          vkGetPrivateData = vkGetPrivateDataEXT;

        //=== VK_KHR_video_encode_queue ===
        vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR = PFN_vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR(
          vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceVideoEncodeQualityLevelPropertiesKHR" ) );
        vkGetEncodedVideoSessionParametersKHR =
          PFN_vkGetEncodedVideoSessionParametersKHR( vkGetInstanceProcAddr( instance, "vkGetEncodedVideoSessionParametersKHR" ) );
        vkCmdEncodeVideoKHR = PFN_vkCmdEncodeVideoKHR( vkGetInstanceProcAddr( instance, "vkCmdEncodeVideoKHR" ) );

        //=== VK_QCOM_queue_perf_hint ===
        vkQueueSetPerfHintQCOM = PFN_vkQueueSetPerfHintQCOM( vkGetInstanceProcAddr( instance, "vkQueueSetPerfHintQCOM" ) );

#if defined( VK_ENABLE_BETA_EXTENSIONS )
        //=== VK_NV_cuda_kernel_launch ===
        vkCreateCudaModuleNV    = PFN_vkCreateCudaModuleNV( vkGetInstanceProcAddr( instance, "vkCreateCudaModuleNV" ) );
        vkGetCudaModuleCacheNV  = PFN_vkGetCudaModuleCacheNV( vkGetInstanceProcAddr( instance, "vkGetCudaModuleCacheNV" ) );
        vkCreateCudaFunctionNV  = PFN_vkCreateCudaFunctionNV( vkGetInstanceProcAddr( instance, "vkCreateCudaFunctionNV" ) );
        vkDestroyCudaModuleNV   = PFN_vkDestroyCudaModuleNV( vkGetInstanceProcAddr( instance, "vkDestroyCudaModuleNV" ) );
        vkDestroyCudaFunctionNV = PFN_vkDestroyCudaFunctionNV( vkGetInstanceProcAddr( instance, "vkDestroyCudaFunctionNV" ) );
        vkCmdCudaLaunchKernelNV = PFN_vkCmdCudaLaunchKernelNV( vkGetInstanceProcAddr( instance, "vkCmdCudaLaunchKernelNV" ) );
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

        //=== VK_QCOM_tile_shading ===
        vkCmdDispatchTileQCOM          = PFN_vkCmdDispatchTileQCOM( vkGetInstanceProcAddr( instance, "vkCmdDispatchTileQCOM" ) );
        vkCmdBeginPerTileExecutionQCOM = PFN_vkCmdBeginPerTileExecutionQCOM( vkGetInstanceProcAddr( instance, "vkCmdBeginPerTileExecutionQCOM" ) );
        vkCmdEndPerTileExecutionQCOM   = PFN_vkCmdEndPerTileExecutionQCOM( vkGetInstanceProcAddr( instance, "vkCmdEndPerTileExecutionQCOM" ) );

#if defined( VK_USE_PLATFORM_METAL_EXT )
        //=== VK_EXT_metal_objects ===
        vkExportMetalObjectsEXT = PFN_vkExportMetalObjectsEXT( vkGetInstanceProcAddr( instance, "vkExportMetalObjectsEXT" ) );
#endif /*VK_USE_PLATFORM_METAL_EXT*/

        //=== VK_KHR_synchronization2 ===
        vkCmdSetEvent2KHR = PFN_vkCmdSetEvent2KHR( vkGetInstanceProcAddr( instance, "vkCmdSetEvent2KHR" ) );
        if ( !vkCmdSetEvent2 )
          vkCmdSetEvent2 = vkCmdSetEvent2KHR;
        vkCmdResetEvent2KHR = PFN_vkCmdResetEvent2KHR( vkGetInstanceProcAddr( instance, "vkCmdResetEvent2KHR" ) );
        if ( !vkCmdResetEvent2 )
          vkCmdResetEvent2 = vkCmdResetEvent2KHR;
        vkCmdWaitEvents2KHR = PFN_vkCmdWaitEvents2KHR( vkGetInstanceProcAddr( instance, "vkCmdWaitEvents2KHR" ) );
        if ( !vkCmdWaitEvents2 )
          vkCmdWaitEvents2 = vkCmdWaitEvents2KHR;
        vkCmdPipelineBarrier2KHR = PFN_vkCmdPipelineBarrier2KHR( vkGetInstanceProcAddr( instance, "vkCmdPipelineBarrier2KHR" ) );
        if ( !vkCmdPipelineBarrier2 )
          vkCmdPipelineBarrier2 = vkCmdPipelineBarrier2KHR;
        vkCmdWriteTimestamp2KHR = PFN_vkCmdWriteTimestamp2KHR( vkGetInstanceProcAddr( instance, "vkCmdWriteTimestamp2KHR" ) );
        if ( !vkCmdWriteTimestamp2 )
          vkCmdWriteTimestamp2 = vkCmdWriteTimestamp2KHR;
        vkQueueSubmit2KHR = PFN_vkQueueSubmit2KHR( vkGetInstanceProcAddr( instance, "vkQueueSubmit2KHR" ) );
        if ( !vkQueueSubmit2 )
          vkQueueSubmit2 = vkQueueSubmit2KHR;

        //=== VK_EXT_descriptor_buffer ===
        vkGetDescriptorSetLayoutSizeEXT = PFN_vkGetDescriptorSetLayoutSizeEXT( vkGetInstanceProcAddr( instance, "vkGetDescriptorSetLayoutSizeEXT" ) );
        vkGetDescriptorSetLayoutBindingOffsetEXT =
          PFN_vkGetDescriptorSetLayoutBindingOffsetEXT( vkGetInstanceProcAddr( instance, "vkGetDescriptorSetLayoutBindingOffsetEXT" ) );
        vkGetDescriptorEXT                 = PFN_vkGetDescriptorEXT( vkGetInstanceProcAddr( instance, "vkGetDescriptorEXT" ) );
        vkCmdBindDescriptorBuffersEXT      = PFN_vkCmdBindDescriptorBuffersEXT( vkGetInstanceProcAddr( instance, "vkCmdBindDescriptorBuffersEXT" ) );
        vkCmdSetDescriptorBufferOffsetsEXT = PFN_vkCmdSetDescriptorBufferOffsetsEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDescriptorBufferOffsetsEXT" ) );
        vkCmdBindDescriptorBufferEmbeddedSamplersEXT =
          PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT( vkGetInstanceProcAddr( instance, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT" ) );
        vkGetBufferOpaqueCaptureDescriptorDataEXT =
          PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT( vkGetInstanceProcAddr( instance, "vkGetBufferOpaqueCaptureDescriptorDataEXT" ) );
        vkGetImageOpaqueCaptureDescriptorDataEXT =
          PFN_vkGetImageOpaqueCaptureDescriptorDataEXT( vkGetInstanceProcAddr( instance, "vkGetImageOpaqueCaptureDescriptorDataEXT" ) );
        vkGetImageViewOpaqueCaptureDescriptorDataEXT =
          PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT( vkGetInstanceProcAddr( instance, "vkGetImageViewOpaqueCaptureDescriptorDataEXT" ) );
        vkGetSamplerOpaqueCaptureDescriptorDataEXT =
          PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT( vkGetInstanceProcAddr( instance, "vkGetSamplerOpaqueCaptureDescriptorDataEXT" ) );
        vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(
          vkGetInstanceProcAddr( instance, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT" ) );

        //=== VK_KHR_device_address_commands ===
        vkCmdBindIndexBuffer3KHR     = PFN_vkCmdBindIndexBuffer3KHR( vkGetInstanceProcAddr( instance, "vkCmdBindIndexBuffer3KHR" ) );
        vkCmdBindVertexBuffers3KHR   = PFN_vkCmdBindVertexBuffers3KHR( vkGetInstanceProcAddr( instance, "vkCmdBindVertexBuffers3KHR" ) );
        vkCmdDrawIndirect2KHR        = PFN_vkCmdDrawIndirect2KHR( vkGetInstanceProcAddr( instance, "vkCmdDrawIndirect2KHR" ) );
        vkCmdDrawIndexedIndirect2KHR = PFN_vkCmdDrawIndexedIndirect2KHR( vkGetInstanceProcAddr( instance, "vkCmdDrawIndexedIndirect2KHR" ) );
        vkCmdDispatchIndirect2KHR    = PFN_vkCmdDispatchIndirect2KHR( vkGetInstanceProcAddr( instance, "vkCmdDispatchIndirect2KHR" ) );
        vkCmdCopyMemoryKHR           = PFN_vkCmdCopyMemoryKHR( vkGetInstanceProcAddr( instance, "vkCmdCopyMemoryKHR" ) );
        vkCmdCopyMemoryToImageKHR    = PFN_vkCmdCopyMemoryToImageKHR( vkGetInstanceProcAddr( instance, "vkCmdCopyMemoryToImageKHR" ) );
        vkCmdCopyImageToMemoryKHR    = PFN_vkCmdCopyImageToMemoryKHR( vkGetInstanceProcAddr( instance, "vkCmdCopyImageToMemoryKHR" ) );
        vkCmdUpdateMemoryKHR         = PFN_vkCmdUpdateMemoryKHR( vkGetInstanceProcAddr( instance, "vkCmdUpdateMemoryKHR" ) );
        vkCmdFillMemoryKHR           = PFN_vkCmdFillMemoryKHR( vkGetInstanceProcAddr( instance, "vkCmdFillMemoryKHR" ) );
        vkCmdCopyQueryPoolResultsToMemoryKHR =
          PFN_vkCmdCopyQueryPoolResultsToMemoryKHR( vkGetInstanceProcAddr( instance, "vkCmdCopyQueryPoolResultsToMemoryKHR" ) );
        vkCmdDrawIndirectCount2KHR         = PFN_vkCmdDrawIndirectCount2KHR( vkGetInstanceProcAddr( instance, "vkCmdDrawIndirectCount2KHR" ) );
        vkCmdDrawIndexedIndirectCount2KHR  = PFN_vkCmdDrawIndexedIndirectCount2KHR( vkGetInstanceProcAddr( instance, "vkCmdDrawIndexedIndirectCount2KHR" ) );
        vkCmdBeginConditionalRendering2EXT = PFN_vkCmdBeginConditionalRendering2EXT( vkGetInstanceProcAddr( instance, "vkCmdBeginConditionalRendering2EXT" ) );
        vkCmdBindTransformFeedbackBuffers2EXT =
          PFN_vkCmdBindTransformFeedbackBuffers2EXT( vkGetInstanceProcAddr( instance, "vkCmdBindTransformFeedbackBuffers2EXT" ) );
        vkCmdBeginTransformFeedback2EXT = PFN_vkCmdBeginTransformFeedback2EXT( vkGetInstanceProcAddr( instance, "vkCmdBeginTransformFeedback2EXT" ) );
        vkCmdEndTransformFeedback2EXT   = PFN_vkCmdEndTransformFeedback2EXT( vkGetInstanceProcAddr( instance, "vkCmdEndTransformFeedback2EXT" ) );
        vkCmdDrawIndirectByteCount2EXT  = PFN_vkCmdDrawIndirectByteCount2EXT( vkGetInstanceProcAddr( instance, "vkCmdDrawIndirectByteCount2EXT" ) );
        vkCmdDrawMeshTasksIndirect2EXT  = PFN_vkCmdDrawMeshTasksIndirect2EXT( vkGetInstanceProcAddr( instance, "vkCmdDrawMeshTasksIndirect2EXT" ) );
        vkCmdDrawMeshTasksIndirectCount2EXT =
          PFN_vkCmdDrawMeshTasksIndirectCount2EXT( vkGetInstanceProcAddr( instance, "vkCmdDrawMeshTasksIndirectCount2EXT" ) );
        vkCmdWriteMarkerToMemoryAMD       = PFN_vkCmdWriteMarkerToMemoryAMD( vkGetInstanceProcAddr( instance, "vkCmdWriteMarkerToMemoryAMD" ) );
        vkCreateAccelerationStructure2KHR = PFN_vkCreateAccelerationStructure2KHR( vkGetInstanceProcAddr( instance, "vkCreateAccelerationStructure2KHR" ) );

        //=== VK_NV_fragment_shading_rate_enums ===
        vkCmdSetFragmentShadingRateEnumNV = PFN_vkCmdSetFragmentShadingRateEnumNV( vkGetInstanceProcAddr( instance, "vkCmdSetFragmentShadingRateEnumNV" ) );

        //=== VK_EXT_mesh_shader ===
        vkCmdDrawMeshTasksEXT              = PFN_vkCmdDrawMeshTasksEXT( vkGetInstanceProcAddr( instance, "vkCmdDrawMeshTasksEXT" ) );
        vkCmdDrawMeshTasksIndirectEXT      = PFN_vkCmdDrawMeshTasksIndirectEXT( vkGetInstanceProcAddr( instance, "vkCmdDrawMeshTasksIndirectEXT" ) );
        vkCmdDrawMeshTasksIndirectCountEXT = PFN_vkCmdDrawMeshTasksIndirectCountEXT( vkGetInstanceProcAddr( instance, "vkCmdDrawMeshTasksIndirectCountEXT" ) );

        //=== VK_KHR_copy_commands2 ===
        vkCmdCopyBuffer2KHR = PFN_vkCmdCopyBuffer2KHR( vkGetInstanceProcAddr( instance, "vkCmdCopyBuffer2KHR" ) );
        if ( !vkCmdCopyBuffer2 )
          vkCmdCopyBuffer2 = vkCmdCopyBuffer2KHR;
        vkCmdCopyImage2KHR = PFN_vkCmdCopyImage2KHR( vkGetInstanceProcAddr( instance, "vkCmdCopyImage2KHR" ) );
        if ( !vkCmdCopyImage2 )
          vkCmdCopyImage2 = vkCmdCopyImage2KHR;
        vkCmdCopyBufferToImage2KHR = PFN_vkCmdCopyBufferToImage2KHR( vkGetInstanceProcAddr( instance, "vkCmdCopyBufferToImage2KHR" ) );
        if ( !vkCmdCopyBufferToImage2 )
          vkCmdCopyBufferToImage2 = vkCmdCopyBufferToImage2KHR;
        vkCmdCopyImageToBuffer2KHR = PFN_vkCmdCopyImageToBuffer2KHR( vkGetInstanceProcAddr( instance, "vkCmdCopyImageToBuffer2KHR" ) );
        if ( !vkCmdCopyImageToBuffer2 )
          vkCmdCopyImageToBuffer2 = vkCmdCopyImageToBuffer2KHR;
        vkCmdBlitImage2KHR = PFN_vkCmdBlitImage2KHR( vkGetInstanceProcAddr( instance, "vkCmdBlitImage2KHR" ) );
        if ( !vkCmdBlitImage2 )
          vkCmdBlitImage2 = vkCmdBlitImage2KHR;
        vkCmdResolveImage2KHR = PFN_vkCmdResolveImage2KHR( vkGetInstanceProcAddr( instance, "vkCmdResolveImage2KHR" ) );
        if ( !vkCmdResolveImage2 )
          vkCmdResolveImage2 = vkCmdResolveImage2KHR;

        //=== VK_EXT_device_fault ===
        vkGetDeviceFaultInfoEXT = PFN_vkGetDeviceFaultInfoEXT( vkGetInstanceProcAddr( instance, "vkGetDeviceFaultInfoEXT" ) );

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_NV_acquire_winrt_display ===
        vkAcquireWinrtDisplayNV = PFN_vkAcquireWinrtDisplayNV( vkGetInstanceProcAddr( instance, "vkAcquireWinrtDisplayNV" ) );
        vkGetWinrtDisplayNV     = PFN_vkGetWinrtDisplayNV( vkGetInstanceProcAddr( instance, "vkGetWinrtDisplayNV" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

#if defined( VK_USE_PLATFORM_DIRECTFB_EXT )
        //=== VK_EXT_directfb_surface ===
        vkCreateDirectFBSurfaceEXT = PFN_vkCreateDirectFBSurfaceEXT( vkGetInstanceProcAddr( instance, "vkCreateDirectFBSurfaceEXT" ) );
        vkGetPhysicalDeviceDirectFBPresentationSupportEXT =
          PFN_vkGetPhysicalDeviceDirectFBPresentationSupportEXT( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceDirectFBPresentationSupportEXT" ) );
#endif /*VK_USE_PLATFORM_DIRECTFB_EXT*/

        //=== VK_EXT_vertex_input_dynamic_state ===
        vkCmdSetVertexInputEXT = PFN_vkCmdSetVertexInputEXT( vkGetInstanceProcAddr( instance, "vkCmdSetVertexInputEXT" ) );

#if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_external_memory ===
        vkGetMemoryZirconHandleFUCHSIA = PFN_vkGetMemoryZirconHandleFUCHSIA( vkGetInstanceProcAddr( instance, "vkGetMemoryZirconHandleFUCHSIA" ) );
        vkGetMemoryZirconHandlePropertiesFUCHSIA =
          PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA( vkGetInstanceProcAddr( instance, "vkGetMemoryZirconHandlePropertiesFUCHSIA" ) );
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_external_semaphore ===
        vkImportSemaphoreZirconHandleFUCHSIA =
          PFN_vkImportSemaphoreZirconHandleFUCHSIA( vkGetInstanceProcAddr( instance, "vkImportSemaphoreZirconHandleFUCHSIA" ) );
        vkGetSemaphoreZirconHandleFUCHSIA = PFN_vkGetSemaphoreZirconHandleFUCHSIA( vkGetInstanceProcAddr( instance, "vkGetSemaphoreZirconHandleFUCHSIA" ) );
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_buffer_collection ===
        vkCreateBufferCollectionFUCHSIA = PFN_vkCreateBufferCollectionFUCHSIA( vkGetInstanceProcAddr( instance, "vkCreateBufferCollectionFUCHSIA" ) );
        vkSetBufferCollectionImageConstraintsFUCHSIA =
          PFN_vkSetBufferCollectionImageConstraintsFUCHSIA( vkGetInstanceProcAddr( instance, "vkSetBufferCollectionImageConstraintsFUCHSIA" ) );
        vkSetBufferCollectionBufferConstraintsFUCHSIA =
          PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA( vkGetInstanceProcAddr( instance, "vkSetBufferCollectionBufferConstraintsFUCHSIA" ) );
        vkDestroyBufferCollectionFUCHSIA = PFN_vkDestroyBufferCollectionFUCHSIA( vkGetInstanceProcAddr( instance, "vkDestroyBufferCollectionFUCHSIA" ) );
        vkGetBufferCollectionPropertiesFUCHSIA =
          PFN_vkGetBufferCollectionPropertiesFUCHSIA( vkGetInstanceProcAddr( instance, "vkGetBufferCollectionPropertiesFUCHSIA" ) );
#endif /*VK_USE_PLATFORM_FUCHSIA*/

        //=== VK_HUAWEI_subpass_shading ===
        vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI =
          PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI( vkGetInstanceProcAddr( instance, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI" ) );
        vkCmdSubpassShadingHUAWEI = PFN_vkCmdSubpassShadingHUAWEI( vkGetInstanceProcAddr( instance, "vkCmdSubpassShadingHUAWEI" ) );

        //=== VK_HUAWEI_invocation_mask ===
        vkCmdBindInvocationMaskHUAWEI = PFN_vkCmdBindInvocationMaskHUAWEI( vkGetInstanceProcAddr( instance, "vkCmdBindInvocationMaskHUAWEI" ) );

        //=== VK_NV_external_memory_rdma ===
        vkGetMemoryRemoteAddressNV = PFN_vkGetMemoryRemoteAddressNV( vkGetInstanceProcAddr( instance, "vkGetMemoryRemoteAddressNV" ) );

        //=== VK_EXT_pipeline_properties ===
        vkGetPipelinePropertiesEXT = PFN_vkGetPipelinePropertiesEXT( vkGetInstanceProcAddr( instance, "vkGetPipelinePropertiesEXT" ) );

        //=== VK_EXT_extended_dynamic_state2 ===
        vkCmdSetPatchControlPointsEXT      = PFN_vkCmdSetPatchControlPointsEXT( vkGetInstanceProcAddr( instance, "vkCmdSetPatchControlPointsEXT" ) );
        vkCmdSetRasterizerDiscardEnableEXT = PFN_vkCmdSetRasterizerDiscardEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetRasterizerDiscardEnableEXT" ) );
        if ( !vkCmdSetRasterizerDiscardEnable )
          vkCmdSetRasterizerDiscardEnable = vkCmdSetRasterizerDiscardEnableEXT;
        vkCmdSetDepthBiasEnableEXT = PFN_vkCmdSetDepthBiasEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDepthBiasEnableEXT" ) );
        if ( !vkCmdSetDepthBiasEnable )
          vkCmdSetDepthBiasEnable = vkCmdSetDepthBiasEnableEXT;
        vkCmdSetLogicOpEXT                = PFN_vkCmdSetLogicOpEXT( vkGetInstanceProcAddr( instance, "vkCmdSetLogicOpEXT" ) );
        vkCmdSetPrimitiveRestartEnableEXT = PFN_vkCmdSetPrimitiveRestartEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetPrimitiveRestartEnableEXT" ) );
        if ( !vkCmdSetPrimitiveRestartEnable )
          vkCmdSetPrimitiveRestartEnable = vkCmdSetPrimitiveRestartEnableEXT;

#if defined( VK_USE_PLATFORM_SCREEN_QNX )
        //=== VK_QNX_screen_surface ===
        vkCreateScreenSurfaceQNX = PFN_vkCreateScreenSurfaceQNX( vkGetInstanceProcAddr( instance, "vkCreateScreenSurfaceQNX" ) );
        vkGetPhysicalDeviceScreenPresentationSupportQNX =
          PFN_vkGetPhysicalDeviceScreenPresentationSupportQNX( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceScreenPresentationSupportQNX" ) );
#endif /*VK_USE_PLATFORM_SCREEN_QNX*/

        //=== VK_EXT_color_write_enable ===
        vkCmdSetColorWriteEnableEXT = PFN_vkCmdSetColorWriteEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetColorWriteEnableEXT" ) );

        //=== VK_KHR_ray_tracing_maintenance1 ===
        vkCmdTraceRaysIndirect2KHR = PFN_vkCmdTraceRaysIndirect2KHR( vkGetInstanceProcAddr( instance, "vkCmdTraceRaysIndirect2KHR" ) );

        //=== VK_EXT_multi_draw ===
        vkCmdDrawMultiEXT        = PFN_vkCmdDrawMultiEXT( vkGetInstanceProcAddr( instance, "vkCmdDrawMultiEXT" ) );
        vkCmdDrawMultiIndexedEXT = PFN_vkCmdDrawMultiIndexedEXT( vkGetInstanceProcAddr( instance, "vkCmdDrawMultiIndexedEXT" ) );

        //=== VK_EXT_opacity_micromap ===
        vkCreateMicromapEXT              = PFN_vkCreateMicromapEXT( vkGetInstanceProcAddr( instance, "vkCreateMicromapEXT" ) );
        vkDestroyMicromapEXT             = PFN_vkDestroyMicromapEXT( vkGetInstanceProcAddr( instance, "vkDestroyMicromapEXT" ) );
        vkCmdBuildMicromapsEXT           = PFN_vkCmdBuildMicromapsEXT( vkGetInstanceProcAddr( instance, "vkCmdBuildMicromapsEXT" ) );
        vkBuildMicromapsEXT              = PFN_vkBuildMicromapsEXT( vkGetInstanceProcAddr( instance, "vkBuildMicromapsEXT" ) );
        vkCopyMicromapEXT                = PFN_vkCopyMicromapEXT( vkGetInstanceProcAddr( instance, "vkCopyMicromapEXT" ) );
        vkCopyMicromapToMemoryEXT        = PFN_vkCopyMicromapToMemoryEXT( vkGetInstanceProcAddr( instance, "vkCopyMicromapToMemoryEXT" ) );
        vkCopyMemoryToMicromapEXT        = PFN_vkCopyMemoryToMicromapEXT( vkGetInstanceProcAddr( instance, "vkCopyMemoryToMicromapEXT" ) );
        vkWriteMicromapsPropertiesEXT    = PFN_vkWriteMicromapsPropertiesEXT( vkGetInstanceProcAddr( instance, "vkWriteMicromapsPropertiesEXT" ) );
        vkCmdCopyMicromapEXT             = PFN_vkCmdCopyMicromapEXT( vkGetInstanceProcAddr( instance, "vkCmdCopyMicromapEXT" ) );
        vkCmdCopyMicromapToMemoryEXT     = PFN_vkCmdCopyMicromapToMemoryEXT( vkGetInstanceProcAddr( instance, "vkCmdCopyMicromapToMemoryEXT" ) );
        vkCmdCopyMemoryToMicromapEXT     = PFN_vkCmdCopyMemoryToMicromapEXT( vkGetInstanceProcAddr( instance, "vkCmdCopyMemoryToMicromapEXT" ) );
        vkCmdWriteMicromapsPropertiesEXT = PFN_vkCmdWriteMicromapsPropertiesEXT( vkGetInstanceProcAddr( instance, "vkCmdWriteMicromapsPropertiesEXT" ) );
        vkGetDeviceMicromapCompatibilityEXT =
          PFN_vkGetDeviceMicromapCompatibilityEXT( vkGetInstanceProcAddr( instance, "vkGetDeviceMicromapCompatibilityEXT" ) );
        vkGetMicromapBuildSizesEXT = PFN_vkGetMicromapBuildSizesEXT( vkGetInstanceProcAddr( instance, "vkGetMicromapBuildSizesEXT" ) );

        //=== VK_HUAWEI_cluster_culling_shader ===
        vkCmdDrawClusterHUAWEI         = PFN_vkCmdDrawClusterHUAWEI( vkGetInstanceProcAddr( instance, "vkCmdDrawClusterHUAWEI" ) );
        vkCmdDrawClusterIndirectHUAWEI = PFN_vkCmdDrawClusterIndirectHUAWEI( vkGetInstanceProcAddr( instance, "vkCmdDrawClusterIndirectHUAWEI" ) );

        //=== VK_EXT_pageable_device_local_memory ===
        vkSetDeviceMemoryPriorityEXT = PFN_vkSetDeviceMemoryPriorityEXT( vkGetInstanceProcAddr( instance, "vkSetDeviceMemoryPriorityEXT" ) );

        //=== VK_KHR_maintenance4 ===
        vkGetDeviceBufferMemoryRequirementsKHR =
          PFN_vkGetDeviceBufferMemoryRequirementsKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceBufferMemoryRequirementsKHR" ) );
        if ( !vkGetDeviceBufferMemoryRequirements )
          vkGetDeviceBufferMemoryRequirements = vkGetDeviceBufferMemoryRequirementsKHR;
        vkGetDeviceImageMemoryRequirementsKHR =
          PFN_vkGetDeviceImageMemoryRequirementsKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceImageMemoryRequirementsKHR" ) );
        if ( !vkGetDeviceImageMemoryRequirements )
          vkGetDeviceImageMemoryRequirements = vkGetDeviceImageMemoryRequirementsKHR;
        vkGetDeviceImageSparseMemoryRequirementsKHR =
          PFN_vkGetDeviceImageSparseMemoryRequirementsKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceImageSparseMemoryRequirementsKHR" ) );
        if ( !vkGetDeviceImageSparseMemoryRequirements )
          vkGetDeviceImageSparseMemoryRequirements = vkGetDeviceImageSparseMemoryRequirementsKHR;

        //=== VK_ARM_scheduling_controls ===
        vkCmdSetDispatchParametersARM = PFN_vkCmdSetDispatchParametersARM( vkGetInstanceProcAddr( instance, "vkCmdSetDispatchParametersARM" ) );

        //=== VK_VALVE_descriptor_set_host_mapping ===
        vkGetDescriptorSetLayoutHostMappingInfoVALVE =
          PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE( vkGetInstanceProcAddr( instance, "vkGetDescriptorSetLayoutHostMappingInfoVALVE" ) );
        vkGetDescriptorSetHostMappingVALVE = PFN_vkGetDescriptorSetHostMappingVALVE( vkGetInstanceProcAddr( instance, "vkGetDescriptorSetHostMappingVALVE" ) );

        //=== VK_NV_copy_memory_indirect ===
        vkCmdCopyMemoryIndirectNV        = PFN_vkCmdCopyMemoryIndirectNV( vkGetInstanceProcAddr( instance, "vkCmdCopyMemoryIndirectNV" ) );
        vkCmdCopyMemoryToImageIndirectNV = PFN_vkCmdCopyMemoryToImageIndirectNV( vkGetInstanceProcAddr( instance, "vkCmdCopyMemoryToImageIndirectNV" ) );

        //=== VK_NV_memory_decompression ===
        vkCmdDecompressMemoryNV = PFN_vkCmdDecompressMemoryNV( vkGetInstanceProcAddr( instance, "vkCmdDecompressMemoryNV" ) );
        vkCmdDecompressMemoryIndirectCountNV =
          PFN_vkCmdDecompressMemoryIndirectCountNV( vkGetInstanceProcAddr( instance, "vkCmdDecompressMemoryIndirectCountNV" ) );

        //=== VK_NV_device_generated_commands_compute ===
        vkGetPipelineIndirectMemoryRequirementsNV =
          PFN_vkGetPipelineIndirectMemoryRequirementsNV( vkGetInstanceProcAddr( instance, "vkGetPipelineIndirectMemoryRequirementsNV" ) );
        vkCmdUpdatePipelineIndirectBufferNV =
          PFN_vkCmdUpdatePipelineIndirectBufferNV( vkGetInstanceProcAddr( instance, "vkCmdUpdatePipelineIndirectBufferNV" ) );
        vkGetPipelineIndirectDeviceAddressNV =
          PFN_vkGetPipelineIndirectDeviceAddressNV( vkGetInstanceProcAddr( instance, "vkGetPipelineIndirectDeviceAddressNV" ) );

#if defined( VK_USE_PLATFORM_OHOS )
        //=== VK_OHOS_external_memory ===
        vkGetNativeBufferPropertiesOHOS = PFN_vkGetNativeBufferPropertiesOHOS( vkGetInstanceProcAddr( instance, "vkGetNativeBufferPropertiesOHOS" ) );
        vkGetMemoryNativeBufferOHOS     = PFN_vkGetMemoryNativeBufferOHOS( vkGetInstanceProcAddr( instance, "vkGetMemoryNativeBufferOHOS" ) );
#endif /*VK_USE_PLATFORM_OHOS*/

        //=== VK_EXT_extended_dynamic_state3 ===
        vkCmdSetDepthClampEnableEXT      = PFN_vkCmdSetDepthClampEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDepthClampEnableEXT" ) );
        vkCmdSetPolygonModeEXT           = PFN_vkCmdSetPolygonModeEXT( vkGetInstanceProcAddr( instance, "vkCmdSetPolygonModeEXT" ) );
        vkCmdSetRasterizationSamplesEXT  = PFN_vkCmdSetRasterizationSamplesEXT( vkGetInstanceProcAddr( instance, "vkCmdSetRasterizationSamplesEXT" ) );
        vkCmdSetSampleMaskEXT            = PFN_vkCmdSetSampleMaskEXT( vkGetInstanceProcAddr( instance, "vkCmdSetSampleMaskEXT" ) );
        vkCmdSetAlphaToCoverageEnableEXT = PFN_vkCmdSetAlphaToCoverageEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetAlphaToCoverageEnableEXT" ) );
        vkCmdSetAlphaToOneEnableEXT      = PFN_vkCmdSetAlphaToOneEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetAlphaToOneEnableEXT" ) );
        vkCmdSetLogicOpEnableEXT         = PFN_vkCmdSetLogicOpEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetLogicOpEnableEXT" ) );
        vkCmdSetColorBlendEnableEXT      = PFN_vkCmdSetColorBlendEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetColorBlendEnableEXT" ) );
        vkCmdSetColorBlendEquationEXT    = PFN_vkCmdSetColorBlendEquationEXT( vkGetInstanceProcAddr( instance, "vkCmdSetColorBlendEquationEXT" ) );
        vkCmdSetColorWriteMaskEXT        = PFN_vkCmdSetColorWriteMaskEXT( vkGetInstanceProcAddr( instance, "vkCmdSetColorWriteMaskEXT" ) );
        vkCmdSetTessellationDomainOriginEXT =
          PFN_vkCmdSetTessellationDomainOriginEXT( vkGetInstanceProcAddr( instance, "vkCmdSetTessellationDomainOriginEXT" ) );
        vkCmdSetRasterizationStreamEXT = PFN_vkCmdSetRasterizationStreamEXT( vkGetInstanceProcAddr( instance, "vkCmdSetRasterizationStreamEXT" ) );
        vkCmdSetConservativeRasterizationModeEXT =
          PFN_vkCmdSetConservativeRasterizationModeEXT( vkGetInstanceProcAddr( instance, "vkCmdSetConservativeRasterizationModeEXT" ) );
        vkCmdSetExtraPrimitiveOverestimationSizeEXT =
          PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT( vkGetInstanceProcAddr( instance, "vkCmdSetExtraPrimitiveOverestimationSizeEXT" ) );
        vkCmdSetDepthClipEnableEXT       = PFN_vkCmdSetDepthClipEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDepthClipEnableEXT" ) );
        vkCmdSetSampleLocationsEnableEXT = PFN_vkCmdSetSampleLocationsEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetSampleLocationsEnableEXT" ) );
        vkCmdSetColorBlendAdvancedEXT    = PFN_vkCmdSetColorBlendAdvancedEXT( vkGetInstanceProcAddr( instance, "vkCmdSetColorBlendAdvancedEXT" ) );
        vkCmdSetProvokingVertexModeEXT   = PFN_vkCmdSetProvokingVertexModeEXT( vkGetInstanceProcAddr( instance, "vkCmdSetProvokingVertexModeEXT" ) );
        vkCmdSetLineRasterizationModeEXT = PFN_vkCmdSetLineRasterizationModeEXT( vkGetInstanceProcAddr( instance, "vkCmdSetLineRasterizationModeEXT" ) );
        vkCmdSetLineStippleEnableEXT     = PFN_vkCmdSetLineStippleEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetLineStippleEnableEXT" ) );
        vkCmdSetDepthClipNegativeOneToOneEXT =
          PFN_vkCmdSetDepthClipNegativeOneToOneEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDepthClipNegativeOneToOneEXT" ) );
        vkCmdSetViewportWScalingEnableNV  = PFN_vkCmdSetViewportWScalingEnableNV( vkGetInstanceProcAddr( instance, "vkCmdSetViewportWScalingEnableNV" ) );
        vkCmdSetViewportSwizzleNV         = PFN_vkCmdSetViewportSwizzleNV( vkGetInstanceProcAddr( instance, "vkCmdSetViewportSwizzleNV" ) );
        vkCmdSetCoverageToColorEnableNV   = PFN_vkCmdSetCoverageToColorEnableNV( vkGetInstanceProcAddr( instance, "vkCmdSetCoverageToColorEnableNV" ) );
        vkCmdSetCoverageToColorLocationNV = PFN_vkCmdSetCoverageToColorLocationNV( vkGetInstanceProcAddr( instance, "vkCmdSetCoverageToColorLocationNV" ) );
        vkCmdSetCoverageModulationModeNV  = PFN_vkCmdSetCoverageModulationModeNV( vkGetInstanceProcAddr( instance, "vkCmdSetCoverageModulationModeNV" ) );
        vkCmdSetCoverageModulationTableEnableNV =
          PFN_vkCmdSetCoverageModulationTableEnableNV( vkGetInstanceProcAddr( instance, "vkCmdSetCoverageModulationTableEnableNV" ) );
        vkCmdSetCoverageModulationTableNV = PFN_vkCmdSetCoverageModulationTableNV( vkGetInstanceProcAddr( instance, "vkCmdSetCoverageModulationTableNV" ) );
        vkCmdSetShadingRateImageEnableNV  = PFN_vkCmdSetShadingRateImageEnableNV( vkGetInstanceProcAddr( instance, "vkCmdSetShadingRateImageEnableNV" ) );
        vkCmdSetRepresentativeFragmentTestEnableNV =
          PFN_vkCmdSetRepresentativeFragmentTestEnableNV( vkGetInstanceProcAddr( instance, "vkCmdSetRepresentativeFragmentTestEnableNV" ) );
        vkCmdSetCoverageReductionModeNV = PFN_vkCmdSetCoverageReductionModeNV( vkGetInstanceProcAddr( instance, "vkCmdSetCoverageReductionModeNV" ) );

        //=== VK_ARM_tensors ===
        vkCreateTensorARM                = PFN_vkCreateTensorARM( vkGetInstanceProcAddr( instance, "vkCreateTensorARM" ) );
        vkDestroyTensorARM               = PFN_vkDestroyTensorARM( vkGetInstanceProcAddr( instance, "vkDestroyTensorARM" ) );
        vkCreateTensorViewARM            = PFN_vkCreateTensorViewARM( vkGetInstanceProcAddr( instance, "vkCreateTensorViewARM" ) );
        vkDestroyTensorViewARM           = PFN_vkDestroyTensorViewARM( vkGetInstanceProcAddr( instance, "vkDestroyTensorViewARM" ) );
        vkGetTensorMemoryRequirementsARM = PFN_vkGetTensorMemoryRequirementsARM( vkGetInstanceProcAddr( instance, "vkGetTensorMemoryRequirementsARM" ) );
        vkBindTensorMemoryARM            = PFN_vkBindTensorMemoryARM( vkGetInstanceProcAddr( instance, "vkBindTensorMemoryARM" ) );
        vkGetDeviceTensorMemoryRequirementsARM =
          PFN_vkGetDeviceTensorMemoryRequirementsARM( vkGetInstanceProcAddr( instance, "vkGetDeviceTensorMemoryRequirementsARM" ) );
        vkCmdCopyTensorARM = PFN_vkCmdCopyTensorARM( vkGetInstanceProcAddr( instance, "vkCmdCopyTensorARM" ) );
        vkGetPhysicalDeviceExternalTensorPropertiesARM =
          PFN_vkGetPhysicalDeviceExternalTensorPropertiesARM( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceExternalTensorPropertiesARM" ) );
        vkGetTensorOpaqueCaptureDescriptorDataARM =
          PFN_vkGetTensorOpaqueCaptureDescriptorDataARM( vkGetInstanceProcAddr( instance, "vkGetTensorOpaqueCaptureDescriptorDataARM" ) );
        vkGetTensorViewOpaqueCaptureDescriptorDataARM =
          PFN_vkGetTensorViewOpaqueCaptureDescriptorDataARM( vkGetInstanceProcAddr( instance, "vkGetTensorViewOpaqueCaptureDescriptorDataARM" ) );

        //=== VK_EXT_shader_module_identifier ===
        vkGetShaderModuleIdentifierEXT = PFN_vkGetShaderModuleIdentifierEXT( vkGetInstanceProcAddr( instance, "vkGetShaderModuleIdentifierEXT" ) );
        vkGetShaderModuleCreateInfoIdentifierEXT =
          PFN_vkGetShaderModuleCreateInfoIdentifierEXT( vkGetInstanceProcAddr( instance, "vkGetShaderModuleCreateInfoIdentifierEXT" ) );

        //=== VK_NV_optical_flow ===
        vkGetPhysicalDeviceOpticalFlowImageFormatsNV =
          PFN_vkGetPhysicalDeviceOpticalFlowImageFormatsNV( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceOpticalFlowImageFormatsNV" ) );
        vkCreateOpticalFlowSessionNV    = PFN_vkCreateOpticalFlowSessionNV( vkGetInstanceProcAddr( instance, "vkCreateOpticalFlowSessionNV" ) );
        vkDestroyOpticalFlowSessionNV   = PFN_vkDestroyOpticalFlowSessionNV( vkGetInstanceProcAddr( instance, "vkDestroyOpticalFlowSessionNV" ) );
        vkBindOpticalFlowSessionImageNV = PFN_vkBindOpticalFlowSessionImageNV( vkGetInstanceProcAddr( instance, "vkBindOpticalFlowSessionImageNV" ) );
        vkCmdOpticalFlowExecuteNV       = PFN_vkCmdOpticalFlowExecuteNV( vkGetInstanceProcAddr( instance, "vkCmdOpticalFlowExecuteNV" ) );

        //=== VK_KHR_maintenance5 ===
        vkCmdBindIndexBuffer2KHR = PFN_vkCmdBindIndexBuffer2KHR( vkGetInstanceProcAddr( instance, "vkCmdBindIndexBuffer2KHR" ) );
        if ( !vkCmdBindIndexBuffer2 )
          vkCmdBindIndexBuffer2 = vkCmdBindIndexBuffer2KHR;
        vkGetRenderingAreaGranularityKHR = PFN_vkGetRenderingAreaGranularityKHR( vkGetInstanceProcAddr( instance, "vkGetRenderingAreaGranularityKHR" ) );
        if ( !vkGetRenderingAreaGranularity )
          vkGetRenderingAreaGranularity = vkGetRenderingAreaGranularityKHR;
        vkGetDeviceImageSubresourceLayoutKHR =
          PFN_vkGetDeviceImageSubresourceLayoutKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceImageSubresourceLayoutKHR" ) );
        if ( !vkGetDeviceImageSubresourceLayout )
          vkGetDeviceImageSubresourceLayout = vkGetDeviceImageSubresourceLayoutKHR;
        vkGetImageSubresourceLayout2KHR = PFN_vkGetImageSubresourceLayout2KHR( vkGetInstanceProcAddr( instance, "vkGetImageSubresourceLayout2KHR" ) );
        if ( !vkGetImageSubresourceLayout2 )
          vkGetImageSubresourceLayout2 = vkGetImageSubresourceLayout2KHR;

        //=== VK_AMD_anti_lag ===
        vkAntiLagUpdateAMD = PFN_vkAntiLagUpdateAMD( vkGetInstanceProcAddr( instance, "vkAntiLagUpdateAMD" ) );

        //=== VK_KHR_present_wait2 ===
        vkWaitForPresent2KHR = PFN_vkWaitForPresent2KHR( vkGetInstanceProcAddr( instance, "vkWaitForPresent2KHR" ) );

        //=== VK_EXT_shader_object ===
        vkCreateShadersEXT         = PFN_vkCreateShadersEXT( vkGetInstanceProcAddr( instance, "vkCreateShadersEXT" ) );
        vkDestroyShaderEXT         = PFN_vkDestroyShaderEXT( vkGetInstanceProcAddr( instance, "vkDestroyShaderEXT" ) );
        vkGetShaderBinaryDataEXT   = PFN_vkGetShaderBinaryDataEXT( vkGetInstanceProcAddr( instance, "vkGetShaderBinaryDataEXT" ) );
        vkCmdBindShadersEXT        = PFN_vkCmdBindShadersEXT( vkGetInstanceProcAddr( instance, "vkCmdBindShadersEXT" ) );
        vkCmdSetDepthClampRangeEXT = PFN_vkCmdSetDepthClampRangeEXT( vkGetInstanceProcAddr( instance, "vkCmdSetDepthClampRangeEXT" ) );

        //=== VK_KHR_pipeline_binary ===
        vkCreatePipelineBinariesKHR      = PFN_vkCreatePipelineBinariesKHR( vkGetInstanceProcAddr( instance, "vkCreatePipelineBinariesKHR" ) );
        vkDestroyPipelineBinaryKHR       = PFN_vkDestroyPipelineBinaryKHR( vkGetInstanceProcAddr( instance, "vkDestroyPipelineBinaryKHR" ) );
        vkGetPipelineKeyKHR              = PFN_vkGetPipelineKeyKHR( vkGetInstanceProcAddr( instance, "vkGetPipelineKeyKHR" ) );
        vkGetPipelineBinaryDataKHR       = PFN_vkGetPipelineBinaryDataKHR( vkGetInstanceProcAddr( instance, "vkGetPipelineBinaryDataKHR" ) );
        vkReleaseCapturedPipelineDataKHR = PFN_vkReleaseCapturedPipelineDataKHR( vkGetInstanceProcAddr( instance, "vkReleaseCapturedPipelineDataKHR" ) );

        //=== VK_QCOM_tile_properties ===
        vkGetFramebufferTilePropertiesQCOM = PFN_vkGetFramebufferTilePropertiesQCOM( vkGetInstanceProcAddr( instance, "vkGetFramebufferTilePropertiesQCOM" ) );
        vkGetDynamicRenderingTilePropertiesQCOM =
          PFN_vkGetDynamicRenderingTilePropertiesQCOM( vkGetInstanceProcAddr( instance, "vkGetDynamicRenderingTilePropertiesQCOM" ) );

        //=== VK_KHR_swapchain_maintenance1 ===
        vkReleaseSwapchainImagesKHR = PFN_vkReleaseSwapchainImagesKHR( vkGetInstanceProcAddr( instance, "vkReleaseSwapchainImagesKHR" ) );

        //=== VK_NV_cooperative_vector ===
        vkGetPhysicalDeviceCooperativeVectorPropertiesNV =
          PFN_vkGetPhysicalDeviceCooperativeVectorPropertiesNV( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceCooperativeVectorPropertiesNV" ) );
        vkConvertCooperativeVectorMatrixNV = PFN_vkConvertCooperativeVectorMatrixNV( vkGetInstanceProcAddr( instance, "vkConvertCooperativeVectorMatrixNV" ) );
        vkCmdConvertCooperativeVectorMatrixNV =
          PFN_vkCmdConvertCooperativeVectorMatrixNV( vkGetInstanceProcAddr( instance, "vkCmdConvertCooperativeVectorMatrixNV" ) );

        //=== VK_NV_low_latency2 ===
        vkSetLatencySleepModeNV  = PFN_vkSetLatencySleepModeNV( vkGetInstanceProcAddr( instance, "vkSetLatencySleepModeNV" ) );
        vkLatencySleepNV         = PFN_vkLatencySleepNV( vkGetInstanceProcAddr( instance, "vkLatencySleepNV" ) );
        vkSetLatencyMarkerNV     = PFN_vkSetLatencyMarkerNV( vkGetInstanceProcAddr( instance, "vkSetLatencyMarkerNV" ) );
        vkGetLatencyTimingsNV    = PFN_vkGetLatencyTimingsNV( vkGetInstanceProcAddr( instance, "vkGetLatencyTimingsNV" ) );
        vkQueueNotifyOutOfBandNV = PFN_vkQueueNotifyOutOfBandNV( vkGetInstanceProcAddr( instance, "vkQueueNotifyOutOfBandNV" ) );

        //=== VK_KHR_cooperative_matrix ===
        vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR =
          PFN_vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceCooperativeMatrixPropertiesKHR" ) );

        //=== VK_ARM_data_graph ===
        vkCreateDataGraphPipelinesARM = PFN_vkCreateDataGraphPipelinesARM( vkGetInstanceProcAddr( instance, "vkCreateDataGraphPipelinesARM" ) );
        vkCreateDataGraphPipelineSessionARM =
          PFN_vkCreateDataGraphPipelineSessionARM( vkGetInstanceProcAddr( instance, "vkCreateDataGraphPipelineSessionARM" ) );
        vkGetDataGraphPipelineSessionBindPointRequirementsARM = PFN_vkGetDataGraphPipelineSessionBindPointRequirementsARM(
          vkGetInstanceProcAddr( instance, "vkGetDataGraphPipelineSessionBindPointRequirementsARM" ) );
        vkGetDataGraphPipelineSessionMemoryRequirementsARM =
          PFN_vkGetDataGraphPipelineSessionMemoryRequirementsARM( vkGetInstanceProcAddr( instance, "vkGetDataGraphPipelineSessionMemoryRequirementsARM" ) );
        vkBindDataGraphPipelineSessionMemoryARM =
          PFN_vkBindDataGraphPipelineSessionMemoryARM( vkGetInstanceProcAddr( instance, "vkBindDataGraphPipelineSessionMemoryARM" ) );
        vkDestroyDataGraphPipelineSessionARM =
          PFN_vkDestroyDataGraphPipelineSessionARM( vkGetInstanceProcAddr( instance, "vkDestroyDataGraphPipelineSessionARM" ) );
        vkCmdDispatchDataGraphARM = PFN_vkCmdDispatchDataGraphARM( vkGetInstanceProcAddr( instance, "vkCmdDispatchDataGraphARM" ) );
        vkGetDataGraphPipelineAvailablePropertiesARM =
          PFN_vkGetDataGraphPipelineAvailablePropertiesARM( vkGetInstanceProcAddr( instance, "vkGetDataGraphPipelineAvailablePropertiesARM" ) );
        vkGetDataGraphPipelinePropertiesARM =
          PFN_vkGetDataGraphPipelinePropertiesARM( vkGetInstanceProcAddr( instance, "vkGetDataGraphPipelinePropertiesARM" ) );
        vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM =
          PFN_vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyDataGraphPropertiesARM" ) );
        vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM = PFN_vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM(
          vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyDataGraphProcessingEnginePropertiesARM" ) );

        //=== VK_ARM_data_graph_instruction_set_tosa ===
        vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM = PFN_vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM(
          vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyDataGraphEngineOperationPropertiesARM" ) );

        //=== VK_EXT_attachment_feedback_loop_dynamic_state ===
        vkCmdSetAttachmentFeedbackLoopEnableEXT =
          PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT( vkGetInstanceProcAddr( instance, "vkCmdSetAttachmentFeedbackLoopEnableEXT" ) );

#if defined( VK_USE_PLATFORM_SCREEN_QNX )
        //=== VK_QNX_external_memory_screen_buffer ===
        vkGetScreenBufferPropertiesQNX = PFN_vkGetScreenBufferPropertiesQNX( vkGetInstanceProcAddr( instance, "vkGetScreenBufferPropertiesQNX" ) );
#endif /*VK_USE_PLATFORM_SCREEN_QNX*/

        //=== VK_KHR_line_rasterization ===
        vkCmdSetLineStippleKHR = PFN_vkCmdSetLineStippleKHR( vkGetInstanceProcAddr( instance, "vkCmdSetLineStippleKHR" ) );
        if ( !vkCmdSetLineStipple )
          vkCmdSetLineStipple = vkCmdSetLineStippleKHR;

        //=== VK_KHR_calibrated_timestamps ===
        vkGetPhysicalDeviceCalibrateableTimeDomainsKHR =
          PFN_vkGetPhysicalDeviceCalibrateableTimeDomainsKHR( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceCalibrateableTimeDomainsKHR" ) );
        vkGetCalibratedTimestampsKHR = PFN_vkGetCalibratedTimestampsKHR( vkGetInstanceProcAddr( instance, "vkGetCalibratedTimestampsKHR" ) );

        //=== VK_KHR_maintenance6 ===
        vkCmdBindDescriptorSets2KHR = PFN_vkCmdBindDescriptorSets2KHR( vkGetInstanceProcAddr( instance, "vkCmdBindDescriptorSets2KHR" ) );
        if ( !vkCmdBindDescriptorSets2 )
          vkCmdBindDescriptorSets2 = vkCmdBindDescriptorSets2KHR;
        vkCmdPushConstants2KHR = PFN_vkCmdPushConstants2KHR( vkGetInstanceProcAddr( instance, "vkCmdPushConstants2KHR" ) );
        if ( !vkCmdPushConstants2 )
          vkCmdPushConstants2 = vkCmdPushConstants2KHR;
        vkCmdPushDescriptorSet2KHR = PFN_vkCmdPushDescriptorSet2KHR( vkGetInstanceProcAddr( instance, "vkCmdPushDescriptorSet2KHR" ) );
        if ( !vkCmdPushDescriptorSet2 )
          vkCmdPushDescriptorSet2 = vkCmdPushDescriptorSet2KHR;
        vkCmdPushDescriptorSetWithTemplate2KHR =
          PFN_vkCmdPushDescriptorSetWithTemplate2KHR( vkGetInstanceProcAddr( instance, "vkCmdPushDescriptorSetWithTemplate2KHR" ) );
        if ( !vkCmdPushDescriptorSetWithTemplate2 )
          vkCmdPushDescriptorSetWithTemplate2 = vkCmdPushDescriptorSetWithTemplate2KHR;
        vkCmdSetDescriptorBufferOffsets2EXT =
          PFN_vkCmdSetDescriptorBufferOffsets2EXT( vkGetInstanceProcAddr( instance, "vkCmdSetDescriptorBufferOffsets2EXT" ) );
        vkCmdBindDescriptorBufferEmbeddedSamplers2EXT =
          PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT( vkGetInstanceProcAddr( instance, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT" ) );

        //=== VK_QCOM_tile_memory_heap ===
        vkCmdBindTileMemoryQCOM = PFN_vkCmdBindTileMemoryQCOM( vkGetInstanceProcAddr( instance, "vkCmdBindTileMemoryQCOM" ) );

        //=== VK_KHR_copy_memory_indirect ===
        vkCmdCopyMemoryIndirectKHR        = PFN_vkCmdCopyMemoryIndirectKHR( vkGetInstanceProcAddr( instance, "vkCmdCopyMemoryIndirectKHR" ) );
        vkCmdCopyMemoryToImageIndirectKHR = PFN_vkCmdCopyMemoryToImageIndirectKHR( vkGetInstanceProcAddr( instance, "vkCmdCopyMemoryToImageIndirectKHR" ) );

        //=== VK_EXT_memory_decompression ===
        vkCmdDecompressMemoryEXT = PFN_vkCmdDecompressMemoryEXT( vkGetInstanceProcAddr( instance, "vkCmdDecompressMemoryEXT" ) );
        vkCmdDecompressMemoryIndirectCountEXT =
          PFN_vkCmdDecompressMemoryIndirectCountEXT( vkGetInstanceProcAddr( instance, "vkCmdDecompressMemoryIndirectCountEXT" ) );

        //=== VK_NV_external_compute_queue ===
        vkCreateExternalComputeQueueNV  = PFN_vkCreateExternalComputeQueueNV( vkGetInstanceProcAddr( instance, "vkCreateExternalComputeQueueNV" ) );
        vkDestroyExternalComputeQueueNV = PFN_vkDestroyExternalComputeQueueNV( vkGetInstanceProcAddr( instance, "vkDestroyExternalComputeQueueNV" ) );
        vkGetExternalComputeQueueDataNV = PFN_vkGetExternalComputeQueueDataNV( vkGetInstanceProcAddr( instance, "vkGetExternalComputeQueueDataNV" ) );

        //=== VK_NV_cluster_acceleration_structure ===
        vkGetClusterAccelerationStructureBuildSizesNV =
          PFN_vkGetClusterAccelerationStructureBuildSizesNV( vkGetInstanceProcAddr( instance, "vkGetClusterAccelerationStructureBuildSizesNV" ) );
        vkCmdBuildClusterAccelerationStructureIndirectNV =
          PFN_vkCmdBuildClusterAccelerationStructureIndirectNV( vkGetInstanceProcAddr( instance, "vkCmdBuildClusterAccelerationStructureIndirectNV" ) );

        //=== VK_NV_partitioned_acceleration_structure ===
        vkGetPartitionedAccelerationStructuresBuildSizesNV =
          PFN_vkGetPartitionedAccelerationStructuresBuildSizesNV( vkGetInstanceProcAddr( instance, "vkGetPartitionedAccelerationStructuresBuildSizesNV" ) );
        vkCmdBuildPartitionedAccelerationStructuresNV =
          PFN_vkCmdBuildPartitionedAccelerationStructuresNV( vkGetInstanceProcAddr( instance, "vkCmdBuildPartitionedAccelerationStructuresNV" ) );

        //=== VK_EXT_device_generated_commands ===
        vkGetGeneratedCommandsMemoryRequirementsEXT =
          PFN_vkGetGeneratedCommandsMemoryRequirementsEXT( vkGetInstanceProcAddr( instance, "vkGetGeneratedCommandsMemoryRequirementsEXT" ) );
        vkCmdPreprocessGeneratedCommandsEXT =
          PFN_vkCmdPreprocessGeneratedCommandsEXT( vkGetInstanceProcAddr( instance, "vkCmdPreprocessGeneratedCommandsEXT" ) );
        vkCmdExecuteGeneratedCommandsEXT   = PFN_vkCmdExecuteGeneratedCommandsEXT( vkGetInstanceProcAddr( instance, "vkCmdExecuteGeneratedCommandsEXT" ) );
        vkCreateIndirectCommandsLayoutEXT  = PFN_vkCreateIndirectCommandsLayoutEXT( vkGetInstanceProcAddr( instance, "vkCreateIndirectCommandsLayoutEXT" ) );
        vkDestroyIndirectCommandsLayoutEXT = PFN_vkDestroyIndirectCommandsLayoutEXT( vkGetInstanceProcAddr( instance, "vkDestroyIndirectCommandsLayoutEXT" ) );
        vkCreateIndirectExecutionSetEXT    = PFN_vkCreateIndirectExecutionSetEXT( vkGetInstanceProcAddr( instance, "vkCreateIndirectExecutionSetEXT" ) );
        vkDestroyIndirectExecutionSetEXT   = PFN_vkDestroyIndirectExecutionSetEXT( vkGetInstanceProcAddr( instance, "vkDestroyIndirectExecutionSetEXT" ) );
        vkUpdateIndirectExecutionSetPipelineEXT =
          PFN_vkUpdateIndirectExecutionSetPipelineEXT( vkGetInstanceProcAddr( instance, "vkUpdateIndirectExecutionSetPipelineEXT" ) );
        vkUpdateIndirectExecutionSetShaderEXT =
          PFN_vkUpdateIndirectExecutionSetShaderEXT( vkGetInstanceProcAddr( instance, "vkUpdateIndirectExecutionSetShaderEXT" ) );

        //=== VK_KHR_device_fault ===
        vkGetDeviceFaultReportsKHR   = PFN_vkGetDeviceFaultReportsKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceFaultReportsKHR" ) );
        vkGetDeviceFaultDebugInfoKHR = PFN_vkGetDeviceFaultDebugInfoKHR( vkGetInstanceProcAddr( instance, "vkGetDeviceFaultDebugInfoKHR" ) );

#if defined( VK_USE_PLATFORM_OHOS )
        //=== VK_OHOS_surface ===
        vkCreateSurfaceOHOS = PFN_vkCreateSurfaceOHOS( vkGetInstanceProcAddr( instance, "vkCreateSurfaceOHOS" ) );
#endif /*VK_USE_PLATFORM_OHOS*/

        //=== VK_NV_cooperative_matrix2 ===
        vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV = PFN_vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV(
          vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceCooperativeMatrixFlexibleDimensionsPropertiesNV" ) );

#if defined( VK_USE_PLATFORM_METAL_EXT )
        //=== VK_EXT_external_memory_metal ===
        vkGetMemoryMetalHandleEXT = PFN_vkGetMemoryMetalHandleEXT( vkGetInstanceProcAddr( instance, "vkGetMemoryMetalHandleEXT" ) );
        vkGetMemoryMetalHandlePropertiesEXT =
          PFN_vkGetMemoryMetalHandlePropertiesEXT( vkGetInstanceProcAddr( instance, "vkGetMemoryMetalHandlePropertiesEXT" ) );
#endif /*VK_USE_PLATFORM_METAL_EXT*/

        //=== VK_ARM_performance_counters_by_region ===
        vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM = PFN_vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM(
          vkGetInstanceProcAddr( instance, "vkEnumeratePhysicalDeviceQueueFamilyPerformanceCountersByRegionARM" ) );

        //=== VK_ARM_shader_instrumentation ===
        vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM = PFN_vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM(
          vkGetInstanceProcAddr( instance, "vkEnumeratePhysicalDeviceShaderInstrumentationMetricsARM" ) );
        vkCreateShaderInstrumentationARM   = PFN_vkCreateShaderInstrumentationARM( vkGetInstanceProcAddr( instance, "vkCreateShaderInstrumentationARM" ) );
        vkDestroyShaderInstrumentationARM  = PFN_vkDestroyShaderInstrumentationARM( vkGetInstanceProcAddr( instance, "vkDestroyShaderInstrumentationARM" ) );
        vkCmdBeginShaderInstrumentationARM = PFN_vkCmdBeginShaderInstrumentationARM( vkGetInstanceProcAddr( instance, "vkCmdBeginShaderInstrumentationARM" ) );
        vkCmdEndShaderInstrumentationARM   = PFN_vkCmdEndShaderInstrumentationARM( vkGetInstanceProcAddr( instance, "vkCmdEndShaderInstrumentationARM" ) );
        vkGetShaderInstrumentationValuesARM =
          PFN_vkGetShaderInstrumentationValuesARM( vkGetInstanceProcAddr( instance, "vkGetShaderInstrumentationValuesARM" ) );
        vkClearShaderInstrumentationMetricsARM =
          PFN_vkClearShaderInstrumentationMetricsARM( vkGetInstanceProcAddr( instance, "vkClearShaderInstrumentationMetricsARM" ) );

        //=== VK_EXT_fragment_density_map_offset ===
        vkCmdEndRendering2EXT = PFN_vkCmdEndRendering2EXT( vkGetInstanceProcAddr( instance, "vkCmdEndRendering2EXT" ) );
        if ( !vkCmdEndRendering2KHR )
          vkCmdEndRendering2KHR = vkCmdEndRendering2EXT;

        //=== VK_EXT_custom_resolve ===
        vkCmdBeginCustomResolveEXT = PFN_vkCmdBeginCustomResolveEXT( vkGetInstanceProcAddr( instance, "vkCmdBeginCustomResolveEXT" ) );

        //=== VK_KHR_maintenance10 ===
        vkCmdEndRendering2KHR = PFN_vkCmdEndRendering2KHR( vkGetInstanceProcAddr( instance, "vkCmdEndRendering2KHR" ) );

        //=== VK_ARM_data_graph_optical_flow ===
        vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM = PFN_vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM(
          vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceQueueFamilyDataGraphOpticalFlowImageFormatsARM" ) );

        //=== VK_NV_compute_occupancy_priority ===
        vkCmdSetComputeOccupancyPriorityNV = PFN_vkCmdSetComputeOccupancyPriorityNV( vkGetInstanceProcAddr( instance, "vkCmdSetComputeOccupancyPriorityNV" ) );

#if defined( VK_USE_PLATFORM_UBM_SEC )
        //=== VK_SEC_ubm_surface ===
        vkCreateUbmSurfaceSEC = PFN_vkCreateUbmSurfaceSEC( vkGetInstanceProcAddr( instance, "vkCreateUbmSurfaceSEC" ) );
        vkGetPhysicalDeviceUbmPresentationSupportSEC =
          PFN_vkGetPhysicalDeviceUbmPresentationSupportSEC( vkGetInstanceProcAddr( instance, "vkGetPhysicalDeviceUbmPresentationSupportSEC" ) );
#endif /*VK_USE_PLATFORM_UBM_SEC*/

        //=== VK_EXT_primitive_restart_index ===
        vkCmdSetPrimitiveRestartIndexEXT = PFN_vkCmdSetPrimitiveRestartIndexEXT( vkGetInstanceProcAddr( instance, "vkCmdSetPrimitiveRestartIndexEXT" ) );
      }

      void init( Device deviceCpp ) VULKAN_HPP_NOEXCEPT
      {
        VkDevice device = static_cast<VkDevice>( deviceCpp );

        //=== VK_VERSION_1_0 ===
        vkGetDeviceProcAddr                = PFN_vkGetDeviceProcAddr( vkGetDeviceProcAddr( device, "vkGetDeviceProcAddr" ) );
        vkDestroyDevice                    = PFN_vkDestroyDevice( vkGetDeviceProcAddr( device, "vkDestroyDevice" ) );
        vkGetDeviceQueue                   = PFN_vkGetDeviceQueue( vkGetDeviceProcAddr( device, "vkGetDeviceQueue" ) );
        vkQueueSubmit                      = PFN_vkQueueSubmit( vkGetDeviceProcAddr( device, "vkQueueSubmit" ) );
        vkQueueWaitIdle                    = PFN_vkQueueWaitIdle( vkGetDeviceProcAddr( device, "vkQueueWaitIdle" ) );
        vkDeviceWaitIdle                   = PFN_vkDeviceWaitIdle( vkGetDeviceProcAddr( device, "vkDeviceWaitIdle" ) );
        vkAllocateMemory                   = PFN_vkAllocateMemory( vkGetDeviceProcAddr( device, "vkAllocateMemory" ) );
        vkFreeMemory                       = PFN_vkFreeMemory( vkGetDeviceProcAddr( device, "vkFreeMemory" ) );
        vkMapMemory                        = PFN_vkMapMemory( vkGetDeviceProcAddr( device, "vkMapMemory" ) );
        vkUnmapMemory                      = PFN_vkUnmapMemory( vkGetDeviceProcAddr( device, "vkUnmapMemory" ) );
        vkFlushMappedMemoryRanges          = PFN_vkFlushMappedMemoryRanges( vkGetDeviceProcAddr( device, "vkFlushMappedMemoryRanges" ) );
        vkInvalidateMappedMemoryRanges     = PFN_vkInvalidateMappedMemoryRanges( vkGetDeviceProcAddr( device, "vkInvalidateMappedMemoryRanges" ) );
        vkGetDeviceMemoryCommitment        = PFN_vkGetDeviceMemoryCommitment( vkGetDeviceProcAddr( device, "vkGetDeviceMemoryCommitment" ) );
        vkBindBufferMemory                 = PFN_vkBindBufferMemory( vkGetDeviceProcAddr( device, "vkBindBufferMemory" ) );
        vkBindImageMemory                  = PFN_vkBindImageMemory( vkGetDeviceProcAddr( device, "vkBindImageMemory" ) );
        vkGetBufferMemoryRequirements      = PFN_vkGetBufferMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetBufferMemoryRequirements" ) );
        vkGetImageMemoryRequirements       = PFN_vkGetImageMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetImageMemoryRequirements" ) );
        vkGetImageSparseMemoryRequirements = PFN_vkGetImageSparseMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetImageSparseMemoryRequirements" ) );
        vkQueueBindSparse                  = PFN_vkQueueBindSparse( vkGetDeviceProcAddr( device, "vkQueueBindSparse" ) );
        vkCreateFence                      = PFN_vkCreateFence( vkGetDeviceProcAddr( device, "vkCreateFence" ) );
        vkDestroyFence                     = PFN_vkDestroyFence( vkGetDeviceProcAddr( device, "vkDestroyFence" ) );
        vkResetFences                      = PFN_vkResetFences( vkGetDeviceProcAddr( device, "vkResetFences" ) );
        vkGetFenceStatus                   = PFN_vkGetFenceStatus( vkGetDeviceProcAddr( device, "vkGetFenceStatus" ) );
        vkWaitForFences                    = PFN_vkWaitForFences( vkGetDeviceProcAddr( device, "vkWaitForFences" ) );
        vkCreateSemaphore                  = PFN_vkCreateSemaphore( vkGetDeviceProcAddr( device, "vkCreateSemaphore" ) );
        vkDestroySemaphore                 = PFN_vkDestroySemaphore( vkGetDeviceProcAddr( device, "vkDestroySemaphore" ) );
        vkCreateQueryPool                  = PFN_vkCreateQueryPool( vkGetDeviceProcAddr( device, "vkCreateQueryPool" ) );
        vkDestroyQueryPool                 = PFN_vkDestroyQueryPool( vkGetDeviceProcAddr( device, "vkDestroyQueryPool" ) );
        vkGetQueryPoolResults              = PFN_vkGetQueryPoolResults( vkGetDeviceProcAddr( device, "vkGetQueryPoolResults" ) );
        vkCreateBuffer                     = PFN_vkCreateBuffer( vkGetDeviceProcAddr( device, "vkCreateBuffer" ) );
        vkDestroyBuffer                    = PFN_vkDestroyBuffer( vkGetDeviceProcAddr( device, "vkDestroyBuffer" ) );
        vkCreateImage                      = PFN_vkCreateImage( vkGetDeviceProcAddr( device, "vkCreateImage" ) );
        vkDestroyImage                     = PFN_vkDestroyImage( vkGetDeviceProcAddr( device, "vkDestroyImage" ) );
        vkGetImageSubresourceLayout        = PFN_vkGetImageSubresourceLayout( vkGetDeviceProcAddr( device, "vkGetImageSubresourceLayout" ) );
        vkCreateImageView                  = PFN_vkCreateImageView( vkGetDeviceProcAddr( device, "vkCreateImageView" ) );
        vkDestroyImageView                 = PFN_vkDestroyImageView( vkGetDeviceProcAddr( device, "vkDestroyImageView" ) );
        vkCreateCommandPool                = PFN_vkCreateCommandPool( vkGetDeviceProcAddr( device, "vkCreateCommandPool" ) );
        vkDestroyCommandPool               = PFN_vkDestroyCommandPool( vkGetDeviceProcAddr( device, "vkDestroyCommandPool" ) );
        vkResetCommandPool                 = PFN_vkResetCommandPool( vkGetDeviceProcAddr( device, "vkResetCommandPool" ) );
        vkAllocateCommandBuffers           = PFN_vkAllocateCommandBuffers( vkGetDeviceProcAddr( device, "vkAllocateCommandBuffers" ) );
        vkFreeCommandBuffers               = PFN_vkFreeCommandBuffers( vkGetDeviceProcAddr( device, "vkFreeCommandBuffers" ) );
        vkBeginCommandBuffer               = PFN_vkBeginCommandBuffer( vkGetDeviceProcAddr( device, "vkBeginCommandBuffer" ) );
        vkEndCommandBuffer                 = PFN_vkEndCommandBuffer( vkGetDeviceProcAddr( device, "vkEndCommandBuffer" ) );
        vkResetCommandBuffer               = PFN_vkResetCommandBuffer( vkGetDeviceProcAddr( device, "vkResetCommandBuffer" ) );
        vkCmdCopyBuffer                    = PFN_vkCmdCopyBuffer( vkGetDeviceProcAddr( device, "vkCmdCopyBuffer" ) );
        vkCmdCopyImage                     = PFN_vkCmdCopyImage( vkGetDeviceProcAddr( device, "vkCmdCopyImage" ) );
        vkCmdCopyBufferToImage             = PFN_vkCmdCopyBufferToImage( vkGetDeviceProcAddr( device, "vkCmdCopyBufferToImage" ) );
        vkCmdCopyImageToBuffer             = PFN_vkCmdCopyImageToBuffer( vkGetDeviceProcAddr( device, "vkCmdCopyImageToBuffer" ) );
        vkCmdUpdateBuffer                  = PFN_vkCmdUpdateBuffer( vkGetDeviceProcAddr( device, "vkCmdUpdateBuffer" ) );
        vkCmdFillBuffer                    = PFN_vkCmdFillBuffer( vkGetDeviceProcAddr( device, "vkCmdFillBuffer" ) );
        vkCmdPipelineBarrier               = PFN_vkCmdPipelineBarrier( vkGetDeviceProcAddr( device, "vkCmdPipelineBarrier" ) );
        vkCmdBeginQuery                    = PFN_vkCmdBeginQuery( vkGetDeviceProcAddr( device, "vkCmdBeginQuery" ) );
        vkCmdEndQuery                      = PFN_vkCmdEndQuery( vkGetDeviceProcAddr( device, "vkCmdEndQuery" ) );
        vkCmdResetQueryPool                = PFN_vkCmdResetQueryPool( vkGetDeviceProcAddr( device, "vkCmdResetQueryPool" ) );
        vkCmdWriteTimestamp                = PFN_vkCmdWriteTimestamp( vkGetDeviceProcAddr( device, "vkCmdWriteTimestamp" ) );
        vkCmdCopyQueryPoolResults          = PFN_vkCmdCopyQueryPoolResults( vkGetDeviceProcAddr( device, "vkCmdCopyQueryPoolResults" ) );
        vkCmdExecuteCommands               = PFN_vkCmdExecuteCommands( vkGetDeviceProcAddr( device, "vkCmdExecuteCommands" ) );
        vkCreateEvent                      = PFN_vkCreateEvent( vkGetDeviceProcAddr( device, "vkCreateEvent" ) );
        vkDestroyEvent                     = PFN_vkDestroyEvent( vkGetDeviceProcAddr( device, "vkDestroyEvent" ) );
        vkGetEventStatus                   = PFN_vkGetEventStatus( vkGetDeviceProcAddr( device, "vkGetEventStatus" ) );
        vkSetEvent                         = PFN_vkSetEvent( vkGetDeviceProcAddr( device, "vkSetEvent" ) );
        vkResetEvent                       = PFN_vkResetEvent( vkGetDeviceProcAddr( device, "vkResetEvent" ) );
        vkCreateBufferView                 = PFN_vkCreateBufferView( vkGetDeviceProcAddr( device, "vkCreateBufferView" ) );
        vkDestroyBufferView                = PFN_vkDestroyBufferView( vkGetDeviceProcAddr( device, "vkDestroyBufferView" ) );
        vkCreateShaderModule               = PFN_vkCreateShaderModule( vkGetDeviceProcAddr( device, "vkCreateShaderModule" ) );
        vkDestroyShaderModule              = PFN_vkDestroyShaderModule( vkGetDeviceProcAddr( device, "vkDestroyShaderModule" ) );
        vkCreatePipelineCache              = PFN_vkCreatePipelineCache( vkGetDeviceProcAddr( device, "vkCreatePipelineCache" ) );
        vkDestroyPipelineCache             = PFN_vkDestroyPipelineCache( vkGetDeviceProcAddr( device, "vkDestroyPipelineCache" ) );
        vkGetPipelineCacheData             = PFN_vkGetPipelineCacheData( vkGetDeviceProcAddr( device, "vkGetPipelineCacheData" ) );
        vkMergePipelineCaches              = PFN_vkMergePipelineCaches( vkGetDeviceProcAddr( device, "vkMergePipelineCaches" ) );
        vkCreateComputePipelines           = PFN_vkCreateComputePipelines( vkGetDeviceProcAddr( device, "vkCreateComputePipelines" ) );
        vkDestroyPipeline                  = PFN_vkDestroyPipeline( vkGetDeviceProcAddr( device, "vkDestroyPipeline" ) );
        vkCreatePipelineLayout             = PFN_vkCreatePipelineLayout( vkGetDeviceProcAddr( device, "vkCreatePipelineLayout" ) );
        vkDestroyPipelineLayout            = PFN_vkDestroyPipelineLayout( vkGetDeviceProcAddr( device, "vkDestroyPipelineLayout" ) );
        vkCreateSampler                    = PFN_vkCreateSampler( vkGetDeviceProcAddr( device, "vkCreateSampler" ) );
        vkDestroySampler                   = PFN_vkDestroySampler( vkGetDeviceProcAddr( device, "vkDestroySampler" ) );
        vkCreateDescriptorSetLayout        = PFN_vkCreateDescriptorSetLayout( vkGetDeviceProcAddr( device, "vkCreateDescriptorSetLayout" ) );
        vkDestroyDescriptorSetLayout       = PFN_vkDestroyDescriptorSetLayout( vkGetDeviceProcAddr( device, "vkDestroyDescriptorSetLayout" ) );
        vkCreateDescriptorPool             = PFN_vkCreateDescriptorPool( vkGetDeviceProcAddr( device, "vkCreateDescriptorPool" ) );
        vkDestroyDescriptorPool            = PFN_vkDestroyDescriptorPool( vkGetDeviceProcAddr( device, "vkDestroyDescriptorPool" ) );
        vkResetDescriptorPool              = PFN_vkResetDescriptorPool( vkGetDeviceProcAddr( device, "vkResetDescriptorPool" ) );
        vkAllocateDescriptorSets           = PFN_vkAllocateDescriptorSets( vkGetDeviceProcAddr( device, "vkAllocateDescriptorSets" ) );
        vkFreeDescriptorSets               = PFN_vkFreeDescriptorSets( vkGetDeviceProcAddr( device, "vkFreeDescriptorSets" ) );
        vkUpdateDescriptorSets             = PFN_vkUpdateDescriptorSets( vkGetDeviceProcAddr( device, "vkUpdateDescriptorSets" ) );
        vkCmdBindPipeline                  = PFN_vkCmdBindPipeline( vkGetDeviceProcAddr( device, "vkCmdBindPipeline" ) );
        vkCmdBindDescriptorSets            = PFN_vkCmdBindDescriptorSets( vkGetDeviceProcAddr( device, "vkCmdBindDescriptorSets" ) );
        vkCmdClearColorImage               = PFN_vkCmdClearColorImage( vkGetDeviceProcAddr( device, "vkCmdClearColorImage" ) );
        vkCmdDispatch                      = PFN_vkCmdDispatch( vkGetDeviceProcAddr( device, "vkCmdDispatch" ) );
        vkCmdDispatchIndirect              = PFN_vkCmdDispatchIndirect( vkGetDeviceProcAddr( device, "vkCmdDispatchIndirect" ) );
        vkCmdSetEvent                      = PFN_vkCmdSetEvent( vkGetDeviceProcAddr( device, "vkCmdSetEvent" ) );
        vkCmdResetEvent                    = PFN_vkCmdResetEvent( vkGetDeviceProcAddr( device, "vkCmdResetEvent" ) );
        vkCmdWaitEvents                    = PFN_vkCmdWaitEvents( vkGetDeviceProcAddr( device, "vkCmdWaitEvents" ) );
        vkCmdPushConstants                 = PFN_vkCmdPushConstants( vkGetDeviceProcAddr( device, "vkCmdPushConstants" ) );
        vkCreateGraphicsPipelines          = PFN_vkCreateGraphicsPipelines( vkGetDeviceProcAddr( device, "vkCreateGraphicsPipelines" ) );
        vkCreateFramebuffer                = PFN_vkCreateFramebuffer( vkGetDeviceProcAddr( device, "vkCreateFramebuffer" ) );
        vkDestroyFramebuffer               = PFN_vkDestroyFramebuffer( vkGetDeviceProcAddr( device, "vkDestroyFramebuffer" ) );
        vkCreateRenderPass                 = PFN_vkCreateRenderPass( vkGetDeviceProcAddr( device, "vkCreateRenderPass" ) );
        vkDestroyRenderPass                = PFN_vkDestroyRenderPass( vkGetDeviceProcAddr( device, "vkDestroyRenderPass" ) );
        vkGetRenderAreaGranularity         = PFN_vkGetRenderAreaGranularity( vkGetDeviceProcAddr( device, "vkGetRenderAreaGranularity" ) );
        vkCmdSetViewport                   = PFN_vkCmdSetViewport( vkGetDeviceProcAddr( device, "vkCmdSetViewport" ) );
        vkCmdSetScissor                    = PFN_vkCmdSetScissor( vkGetDeviceProcAddr( device, "vkCmdSetScissor" ) );
        vkCmdSetLineWidth                  = PFN_vkCmdSetLineWidth( vkGetDeviceProcAddr( device, "vkCmdSetLineWidth" ) );
        vkCmdSetDepthBias                  = PFN_vkCmdSetDepthBias( vkGetDeviceProcAddr( device, "vkCmdSetDepthBias" ) );
        vkCmdSetBlendConstants             = PFN_vkCmdSetBlendConstants( vkGetDeviceProcAddr( device, "vkCmdSetBlendConstants" ) );
        vkCmdSetDepthBounds                = PFN_vkCmdSetDepthBounds( vkGetDeviceProcAddr( device, "vkCmdSetDepthBounds" ) );
        vkCmdSetStencilCompareMask         = PFN_vkCmdSetStencilCompareMask( vkGetDeviceProcAddr( device, "vkCmdSetStencilCompareMask" ) );
        vkCmdSetStencilWriteMask           = PFN_vkCmdSetStencilWriteMask( vkGetDeviceProcAddr( device, "vkCmdSetStencilWriteMask" ) );
        vkCmdSetStencilReference           = PFN_vkCmdSetStencilReference( vkGetDeviceProcAddr( device, "vkCmdSetStencilReference" ) );
        vkCmdBindIndexBuffer               = PFN_vkCmdBindIndexBuffer( vkGetDeviceProcAddr( device, "vkCmdBindIndexBuffer" ) );
        vkCmdBindVertexBuffers             = PFN_vkCmdBindVertexBuffers( vkGetDeviceProcAddr( device, "vkCmdBindVertexBuffers" ) );
        vkCmdDraw                          = PFN_vkCmdDraw( vkGetDeviceProcAddr( device, "vkCmdDraw" ) );
        vkCmdDrawIndexed                   = PFN_vkCmdDrawIndexed( vkGetDeviceProcAddr( device, "vkCmdDrawIndexed" ) );
        vkCmdDrawIndirect                  = PFN_vkCmdDrawIndirect( vkGetDeviceProcAddr( device, "vkCmdDrawIndirect" ) );
        vkCmdDrawIndexedIndirect           = PFN_vkCmdDrawIndexedIndirect( vkGetDeviceProcAddr( device, "vkCmdDrawIndexedIndirect" ) );
        vkCmdBlitImage                     = PFN_vkCmdBlitImage( vkGetDeviceProcAddr( device, "vkCmdBlitImage" ) );
        vkCmdClearDepthStencilImage        = PFN_vkCmdClearDepthStencilImage( vkGetDeviceProcAddr( device, "vkCmdClearDepthStencilImage" ) );
        vkCmdClearAttachments              = PFN_vkCmdClearAttachments( vkGetDeviceProcAddr( device, "vkCmdClearAttachments" ) );
        vkCmdResolveImage                  = PFN_vkCmdResolveImage( vkGetDeviceProcAddr( device, "vkCmdResolveImage" ) );
        vkCmdBeginRenderPass               = PFN_vkCmdBeginRenderPass( vkGetDeviceProcAddr( device, "vkCmdBeginRenderPass" ) );
        vkCmdNextSubpass                   = PFN_vkCmdNextSubpass( vkGetDeviceProcAddr( device, "vkCmdNextSubpass" ) );
        vkCmdEndRenderPass                 = PFN_vkCmdEndRenderPass( vkGetDeviceProcAddr( device, "vkCmdEndRenderPass" ) );

        //=== VK_VERSION_1_1 ===
        vkBindBufferMemory2                 = PFN_vkBindBufferMemory2( vkGetDeviceProcAddr( device, "vkBindBufferMemory2" ) );
        vkBindImageMemory2                  = PFN_vkBindImageMemory2( vkGetDeviceProcAddr( device, "vkBindImageMemory2" ) );
        vkGetDeviceGroupPeerMemoryFeatures  = PFN_vkGetDeviceGroupPeerMemoryFeatures( vkGetDeviceProcAddr( device, "vkGetDeviceGroupPeerMemoryFeatures" ) );
        vkCmdSetDeviceMask                  = PFN_vkCmdSetDeviceMask( vkGetDeviceProcAddr( device, "vkCmdSetDeviceMask" ) );
        vkGetImageMemoryRequirements2       = PFN_vkGetImageMemoryRequirements2( vkGetDeviceProcAddr( device, "vkGetImageMemoryRequirements2" ) );
        vkGetBufferMemoryRequirements2      = PFN_vkGetBufferMemoryRequirements2( vkGetDeviceProcAddr( device, "vkGetBufferMemoryRequirements2" ) );
        vkGetImageSparseMemoryRequirements2 = PFN_vkGetImageSparseMemoryRequirements2( vkGetDeviceProcAddr( device, "vkGetImageSparseMemoryRequirements2" ) );
        vkTrimCommandPool                   = PFN_vkTrimCommandPool( vkGetDeviceProcAddr( device, "vkTrimCommandPool" ) );
        vkGetDeviceQueue2                   = PFN_vkGetDeviceQueue2( vkGetDeviceProcAddr( device, "vkGetDeviceQueue2" ) );
        vkCmdDispatchBase                   = PFN_vkCmdDispatchBase( vkGetDeviceProcAddr( device, "vkCmdDispatchBase" ) );
        vkCreateDescriptorUpdateTemplate    = PFN_vkCreateDescriptorUpdateTemplate( vkGetDeviceProcAddr( device, "vkCreateDescriptorUpdateTemplate" ) );
        vkDestroyDescriptorUpdateTemplate   = PFN_vkDestroyDescriptorUpdateTemplate( vkGetDeviceProcAddr( device, "vkDestroyDescriptorUpdateTemplate" ) );
        vkUpdateDescriptorSetWithTemplate   = PFN_vkUpdateDescriptorSetWithTemplate( vkGetDeviceProcAddr( device, "vkUpdateDescriptorSetWithTemplate" ) );
        vkGetDescriptorSetLayoutSupport     = PFN_vkGetDescriptorSetLayoutSupport( vkGetDeviceProcAddr( device, "vkGetDescriptorSetLayoutSupport" ) );
        vkCreateSamplerYcbcrConversion      = PFN_vkCreateSamplerYcbcrConversion( vkGetDeviceProcAddr( device, "vkCreateSamplerYcbcrConversion" ) );
        vkDestroySamplerYcbcrConversion     = PFN_vkDestroySamplerYcbcrConversion( vkGetDeviceProcAddr( device, "vkDestroySamplerYcbcrConversion" ) );

        //=== VK_VERSION_1_2 ===
        vkResetQueryPool                = PFN_vkResetQueryPool( vkGetDeviceProcAddr( device, "vkResetQueryPool" ) );
        vkGetSemaphoreCounterValue      = PFN_vkGetSemaphoreCounterValue( vkGetDeviceProcAddr( device, "vkGetSemaphoreCounterValue" ) );
        vkWaitSemaphores                = PFN_vkWaitSemaphores( vkGetDeviceProcAddr( device, "vkWaitSemaphores" ) );
        vkSignalSemaphore               = PFN_vkSignalSemaphore( vkGetDeviceProcAddr( device, "vkSignalSemaphore" ) );
        vkGetBufferDeviceAddress        = PFN_vkGetBufferDeviceAddress( vkGetDeviceProcAddr( device, "vkGetBufferDeviceAddress" ) );
        vkGetBufferOpaqueCaptureAddress = PFN_vkGetBufferOpaqueCaptureAddress( vkGetDeviceProcAddr( device, "vkGetBufferOpaqueCaptureAddress" ) );
        vkGetDeviceMemoryOpaqueCaptureAddress =
          PFN_vkGetDeviceMemoryOpaqueCaptureAddress( vkGetDeviceProcAddr( device, "vkGetDeviceMemoryOpaqueCaptureAddress" ) );
        vkCmdDrawIndirectCount        = PFN_vkCmdDrawIndirectCount( vkGetDeviceProcAddr( device, "vkCmdDrawIndirectCount" ) );
        vkCmdDrawIndexedIndirectCount = PFN_vkCmdDrawIndexedIndirectCount( vkGetDeviceProcAddr( device, "vkCmdDrawIndexedIndirectCount" ) );
        vkCreateRenderPass2           = PFN_vkCreateRenderPass2( vkGetDeviceProcAddr( device, "vkCreateRenderPass2" ) );
        vkCmdBeginRenderPass2         = PFN_vkCmdBeginRenderPass2( vkGetDeviceProcAddr( device, "vkCmdBeginRenderPass2" ) );
        vkCmdNextSubpass2             = PFN_vkCmdNextSubpass2( vkGetDeviceProcAddr( device, "vkCmdNextSubpass2" ) );
        vkCmdEndRenderPass2           = PFN_vkCmdEndRenderPass2( vkGetDeviceProcAddr( device, "vkCmdEndRenderPass2" ) );

        //=== VK_VERSION_1_3 ===
        vkCreatePrivateDataSlot             = PFN_vkCreatePrivateDataSlot( vkGetDeviceProcAddr( device, "vkCreatePrivateDataSlot" ) );
        vkDestroyPrivateDataSlot            = PFN_vkDestroyPrivateDataSlot( vkGetDeviceProcAddr( device, "vkDestroyPrivateDataSlot" ) );
        vkSetPrivateData                    = PFN_vkSetPrivateData( vkGetDeviceProcAddr( device, "vkSetPrivateData" ) );
        vkGetPrivateData                    = PFN_vkGetPrivateData( vkGetDeviceProcAddr( device, "vkGetPrivateData" ) );
        vkCmdPipelineBarrier2               = PFN_vkCmdPipelineBarrier2( vkGetDeviceProcAddr( device, "vkCmdPipelineBarrier2" ) );
        vkCmdWriteTimestamp2                = PFN_vkCmdWriteTimestamp2( vkGetDeviceProcAddr( device, "vkCmdWriteTimestamp2" ) );
        vkQueueSubmit2                      = PFN_vkQueueSubmit2( vkGetDeviceProcAddr( device, "vkQueueSubmit2" ) );
        vkCmdCopyBuffer2                    = PFN_vkCmdCopyBuffer2( vkGetDeviceProcAddr( device, "vkCmdCopyBuffer2" ) );
        vkCmdCopyImage2                     = PFN_vkCmdCopyImage2( vkGetDeviceProcAddr( device, "vkCmdCopyImage2" ) );
        vkCmdCopyBufferToImage2             = PFN_vkCmdCopyBufferToImage2( vkGetDeviceProcAddr( device, "vkCmdCopyBufferToImage2" ) );
        vkCmdCopyImageToBuffer2             = PFN_vkCmdCopyImageToBuffer2( vkGetDeviceProcAddr( device, "vkCmdCopyImageToBuffer2" ) );
        vkGetDeviceBufferMemoryRequirements = PFN_vkGetDeviceBufferMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetDeviceBufferMemoryRequirements" ) );
        vkGetDeviceImageMemoryRequirements  = PFN_vkGetDeviceImageMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetDeviceImageMemoryRequirements" ) );
        vkGetDeviceImageSparseMemoryRequirements =
          PFN_vkGetDeviceImageSparseMemoryRequirements( vkGetDeviceProcAddr( device, "vkGetDeviceImageSparseMemoryRequirements" ) );
        vkCmdSetEvent2                  = PFN_vkCmdSetEvent2( vkGetDeviceProcAddr( device, "vkCmdSetEvent2" ) );
        vkCmdResetEvent2                = PFN_vkCmdResetEvent2( vkGetDeviceProcAddr( device, "vkCmdResetEvent2" ) );
        vkCmdWaitEvents2                = PFN_vkCmdWaitEvents2( vkGetDeviceProcAddr( device, "vkCmdWaitEvents2" ) );
        vkCmdBlitImage2                 = PFN_vkCmdBlitImage2( vkGetDeviceProcAddr( device, "vkCmdBlitImage2" ) );
        vkCmdResolveImage2              = PFN_vkCmdResolveImage2( vkGetDeviceProcAddr( device, "vkCmdResolveImage2" ) );
        vkCmdBeginRendering             = PFN_vkCmdBeginRendering( vkGetDeviceProcAddr( device, "vkCmdBeginRendering" ) );
        vkCmdEndRendering               = PFN_vkCmdEndRendering( vkGetDeviceProcAddr( device, "vkCmdEndRendering" ) );
        vkCmdSetCullMode                = PFN_vkCmdSetCullMode( vkGetDeviceProcAddr( device, "vkCmdSetCullMode" ) );
        vkCmdSetFrontFace               = PFN_vkCmdSetFrontFace( vkGetDeviceProcAddr( device, "vkCmdSetFrontFace" ) );
        vkCmdSetPrimitiveTopology       = PFN_vkCmdSetPrimitiveTopology( vkGetDeviceProcAddr( device, "vkCmdSetPrimitiveTopology" ) );
        vkCmdSetViewportWithCount       = PFN_vkCmdSetViewportWithCount( vkGetDeviceProcAddr( device, "vkCmdSetViewportWithCount" ) );
        vkCmdSetScissorWithCount        = PFN_vkCmdSetScissorWithCount( vkGetDeviceProcAddr( device, "vkCmdSetScissorWithCount" ) );
        vkCmdBindVertexBuffers2         = PFN_vkCmdBindVertexBuffers2( vkGetDeviceProcAddr( device, "vkCmdBindVertexBuffers2" ) );
        vkCmdSetDepthTestEnable         = PFN_vkCmdSetDepthTestEnable( vkGetDeviceProcAddr( device, "vkCmdSetDepthTestEnable" ) );
        vkCmdSetDepthWriteEnable        = PFN_vkCmdSetDepthWriteEnable( vkGetDeviceProcAddr( device, "vkCmdSetDepthWriteEnable" ) );
        vkCmdSetDepthCompareOp          = PFN_vkCmdSetDepthCompareOp( vkGetDeviceProcAddr( device, "vkCmdSetDepthCompareOp" ) );
        vkCmdSetDepthBoundsTestEnable   = PFN_vkCmdSetDepthBoundsTestEnable( vkGetDeviceProcAddr( device, "vkCmdSetDepthBoundsTestEnable" ) );
        vkCmdSetStencilTestEnable       = PFN_vkCmdSetStencilTestEnable( vkGetDeviceProcAddr( device, "vkCmdSetStencilTestEnable" ) );
        vkCmdSetStencilOp               = PFN_vkCmdSetStencilOp( vkGetDeviceProcAddr( device, "vkCmdSetStencilOp" ) );
        vkCmdSetRasterizerDiscardEnable = PFN_vkCmdSetRasterizerDiscardEnable( vkGetDeviceProcAddr( device, "vkCmdSetRasterizerDiscardEnable" ) );
        vkCmdSetDepthBiasEnable         = PFN_vkCmdSetDepthBiasEnable( vkGetDeviceProcAddr( device, "vkCmdSetDepthBiasEnable" ) );
        vkCmdSetPrimitiveRestartEnable  = PFN_vkCmdSetPrimitiveRestartEnable( vkGetDeviceProcAddr( device, "vkCmdSetPrimitiveRestartEnable" ) );

        //=== VK_VERSION_1_4 ===
        vkMapMemory2                        = PFN_vkMapMemory2( vkGetDeviceProcAddr( device, "vkMapMemory2" ) );
        vkUnmapMemory2                      = PFN_vkUnmapMemory2( vkGetDeviceProcAddr( device, "vkUnmapMemory2" ) );
        vkGetDeviceImageSubresourceLayout   = PFN_vkGetDeviceImageSubresourceLayout( vkGetDeviceProcAddr( device, "vkGetDeviceImageSubresourceLayout" ) );
        vkGetImageSubresourceLayout2        = PFN_vkGetImageSubresourceLayout2( vkGetDeviceProcAddr( device, "vkGetImageSubresourceLayout2" ) );
        vkCopyMemoryToImage                 = PFN_vkCopyMemoryToImage( vkGetDeviceProcAddr( device, "vkCopyMemoryToImage" ) );
        vkCopyImageToMemory                 = PFN_vkCopyImageToMemory( vkGetDeviceProcAddr( device, "vkCopyImageToMemory" ) );
        vkCopyImageToImage                  = PFN_vkCopyImageToImage( vkGetDeviceProcAddr( device, "vkCopyImageToImage" ) );
        vkTransitionImageLayout             = PFN_vkTransitionImageLayout( vkGetDeviceProcAddr( device, "vkTransitionImageLayout" ) );
        vkCmdPushDescriptorSet              = PFN_vkCmdPushDescriptorSet( vkGetDeviceProcAddr( device, "vkCmdPushDescriptorSet" ) );
        vkCmdPushDescriptorSetWithTemplate  = PFN_vkCmdPushDescriptorSetWithTemplate( vkGetDeviceProcAddr( device, "vkCmdPushDescriptorSetWithTemplate" ) );
        vkCmdBindDescriptorSets2            = PFN_vkCmdBindDescriptorSets2( vkGetDeviceProcAddr( device, "vkCmdBindDescriptorSets2" ) );
        vkCmdPushConstants2                 = PFN_vkCmdPushConstants2( vkGetDeviceProcAddr( device, "vkCmdPushConstants2" ) );
        vkCmdPushDescriptorSet2             = PFN_vkCmdPushDescriptorSet2( vkGetDeviceProcAddr( device, "vkCmdPushDescriptorSet2" ) );
        vkCmdPushDescriptorSetWithTemplate2 = PFN_vkCmdPushDescriptorSetWithTemplate2( vkGetDeviceProcAddr( device, "vkCmdPushDescriptorSetWithTemplate2" ) );
        vkCmdSetLineStipple                 = PFN_vkCmdSetLineStipple( vkGetDeviceProcAddr( device, "vkCmdSetLineStipple" ) );
        vkCmdBindIndexBuffer2               = PFN_vkCmdBindIndexBuffer2( vkGetDeviceProcAddr( device, "vkCmdBindIndexBuffer2" ) );
        vkGetRenderingAreaGranularity       = PFN_vkGetRenderingAreaGranularity( vkGetDeviceProcAddr( device, "vkGetRenderingAreaGranularity" ) );
        vkCmdSetRenderingAttachmentLocations =
          PFN_vkCmdSetRenderingAttachmentLocations( vkGetDeviceProcAddr( device, "vkCmdSetRenderingAttachmentLocations" ) );
        vkCmdSetRenderingInputAttachmentIndices =
          PFN_vkCmdSetRenderingInputAttachmentIndices( vkGetDeviceProcAddr( device, "vkCmdSetRenderingInputAttachmentIndices" ) );

        //=== VK_KHR_swapchain ===
        vkCreateSwapchainKHR    = PFN_vkCreateSwapchainKHR( vkGetDeviceProcAddr( device, "vkCreateSwapchainKHR" ) );
        vkDestroySwapchainKHR   = PFN_vkDestroySwapchainKHR( vkGetDeviceProcAddr( device, "vkDestroySwapchainKHR" ) );
        vkGetSwapchainImagesKHR = PFN_vkGetSwapchainImagesKHR( vkGetDeviceProcAddr( device, "vkGetSwapchainImagesKHR" ) );
        vkAcquireNextImageKHR   = PFN_vkAcquireNextImageKHR( vkGetDeviceProcAddr( device, "vkAcquireNextImageKHR" ) );
        vkQueuePresentKHR       = PFN_vkQueuePresentKHR( vkGetDeviceProcAddr( device, "vkQueuePresentKHR" ) );
        vkGetDeviceGroupPresentCapabilitiesKHR =
          PFN_vkGetDeviceGroupPresentCapabilitiesKHR( vkGetDeviceProcAddr( device, "vkGetDeviceGroupPresentCapabilitiesKHR" ) );
        vkGetDeviceGroupSurfacePresentModesKHR =
          PFN_vkGetDeviceGroupSurfacePresentModesKHR( vkGetDeviceProcAddr( device, "vkGetDeviceGroupSurfacePresentModesKHR" ) );
        vkAcquireNextImage2KHR = PFN_vkAcquireNextImage2KHR( vkGetDeviceProcAddr( device, "vkAcquireNextImage2KHR" ) );

        //=== VK_KHR_display_swapchain ===
        vkCreateSharedSwapchainsKHR = PFN_vkCreateSharedSwapchainsKHR( vkGetDeviceProcAddr( device, "vkCreateSharedSwapchainsKHR" ) );

        //=== VK_EXT_debug_marker ===
        vkDebugMarkerSetObjectTagEXT  = PFN_vkDebugMarkerSetObjectTagEXT( vkGetDeviceProcAddr( device, "vkDebugMarkerSetObjectTagEXT" ) );
        vkDebugMarkerSetObjectNameEXT = PFN_vkDebugMarkerSetObjectNameEXT( vkGetDeviceProcAddr( device, "vkDebugMarkerSetObjectNameEXT" ) );
        vkCmdDebugMarkerBeginEXT      = PFN_vkCmdDebugMarkerBeginEXT( vkGetDeviceProcAddr( device, "vkCmdDebugMarkerBeginEXT" ) );
        vkCmdDebugMarkerEndEXT        = PFN_vkCmdDebugMarkerEndEXT( vkGetDeviceProcAddr( device, "vkCmdDebugMarkerEndEXT" ) );
        vkCmdDebugMarkerInsertEXT     = PFN_vkCmdDebugMarkerInsertEXT( vkGetDeviceProcAddr( device, "vkCmdDebugMarkerInsertEXT" ) );

        //=== VK_KHR_video_queue ===
        vkCreateVideoSessionKHR  = PFN_vkCreateVideoSessionKHR( vkGetDeviceProcAddr( device, "vkCreateVideoSessionKHR" ) );
        vkDestroyVideoSessionKHR = PFN_vkDestroyVideoSessionKHR( vkGetDeviceProcAddr( device, "vkDestroyVideoSessionKHR" ) );
        vkGetVideoSessionMemoryRequirementsKHR =
          PFN_vkGetVideoSessionMemoryRequirementsKHR( vkGetDeviceProcAddr( device, "vkGetVideoSessionMemoryRequirementsKHR" ) );
        vkBindVideoSessionMemoryKHR        = PFN_vkBindVideoSessionMemoryKHR( vkGetDeviceProcAddr( device, "vkBindVideoSessionMemoryKHR" ) );
        vkCreateVideoSessionParametersKHR  = PFN_vkCreateVideoSessionParametersKHR( vkGetDeviceProcAddr( device, "vkCreateVideoSessionParametersKHR" ) );
        vkUpdateVideoSessionParametersKHR  = PFN_vkUpdateVideoSessionParametersKHR( vkGetDeviceProcAddr( device, "vkUpdateVideoSessionParametersKHR" ) );
        vkDestroyVideoSessionParametersKHR = PFN_vkDestroyVideoSessionParametersKHR( vkGetDeviceProcAddr( device, "vkDestroyVideoSessionParametersKHR" ) );
        vkCmdBeginVideoCodingKHR           = PFN_vkCmdBeginVideoCodingKHR( vkGetDeviceProcAddr( device, "vkCmdBeginVideoCodingKHR" ) );
        vkCmdEndVideoCodingKHR             = PFN_vkCmdEndVideoCodingKHR( vkGetDeviceProcAddr( device, "vkCmdEndVideoCodingKHR" ) );
        vkCmdControlVideoCodingKHR         = PFN_vkCmdControlVideoCodingKHR( vkGetDeviceProcAddr( device, "vkCmdControlVideoCodingKHR" ) );

        //=== VK_KHR_video_decode_queue ===
        vkCmdDecodeVideoKHR = PFN_vkCmdDecodeVideoKHR( vkGetDeviceProcAddr( device, "vkCmdDecodeVideoKHR" ) );

        //=== VK_EXT_transform_feedback ===
        vkCmdBindTransformFeedbackBuffersEXT =
          PFN_vkCmdBindTransformFeedbackBuffersEXT( vkGetDeviceProcAddr( device, "vkCmdBindTransformFeedbackBuffersEXT" ) );
        vkCmdBeginTransformFeedbackEXT = PFN_vkCmdBeginTransformFeedbackEXT( vkGetDeviceProcAddr( device, "vkCmdBeginTransformFeedbackEXT" ) );
        vkCmdEndTransformFeedbackEXT   = PFN_vkCmdEndTransformFeedbackEXT( vkGetDeviceProcAddr( device, "vkCmdEndTransformFeedbackEXT" ) );
        vkCmdBeginQueryIndexedEXT      = PFN_vkCmdBeginQueryIndexedEXT( vkGetDeviceProcAddr( device, "vkCmdBeginQueryIndexedEXT" ) );
        vkCmdEndQueryIndexedEXT        = PFN_vkCmdEndQueryIndexedEXT( vkGetDeviceProcAddr( device, "vkCmdEndQueryIndexedEXT" ) );
        vkCmdDrawIndirectByteCountEXT  = PFN_vkCmdDrawIndirectByteCountEXT( vkGetDeviceProcAddr( device, "vkCmdDrawIndirectByteCountEXT" ) );

        //=== VK_NVX_binary_import ===
        vkCreateCuModuleNVX    = PFN_vkCreateCuModuleNVX( vkGetDeviceProcAddr( device, "vkCreateCuModuleNVX" ) );
        vkCreateCuFunctionNVX  = PFN_vkCreateCuFunctionNVX( vkGetDeviceProcAddr( device, "vkCreateCuFunctionNVX" ) );
        vkDestroyCuModuleNVX   = PFN_vkDestroyCuModuleNVX( vkGetDeviceProcAddr( device, "vkDestroyCuModuleNVX" ) );
        vkDestroyCuFunctionNVX = PFN_vkDestroyCuFunctionNVX( vkGetDeviceProcAddr( device, "vkDestroyCuFunctionNVX" ) );
        vkCmdCuLaunchKernelNVX = PFN_vkCmdCuLaunchKernelNVX( vkGetDeviceProcAddr( device, "vkCmdCuLaunchKernelNVX" ) );

        //=== VK_NVX_image_view_handle ===
        vkGetImageViewHandleNVX   = PFN_vkGetImageViewHandleNVX( vkGetDeviceProcAddr( device, "vkGetImageViewHandleNVX" ) );
        vkGetImageViewHandle64NVX = PFN_vkGetImageViewHandle64NVX( vkGetDeviceProcAddr( device, "vkGetImageViewHandle64NVX" ) );
        vkGetImageViewAddressNVX  = PFN_vkGetImageViewAddressNVX( vkGetDeviceProcAddr( device, "vkGetImageViewAddressNVX" ) );
        vkGetDeviceCombinedImageSamplerIndexNVX =
          PFN_vkGetDeviceCombinedImageSamplerIndexNVX( vkGetDeviceProcAddr( device, "vkGetDeviceCombinedImageSamplerIndexNVX" ) );

        //=== VK_AMD_draw_indirect_count ===
        vkCmdDrawIndirectCountAMD = PFN_vkCmdDrawIndirectCountAMD( vkGetDeviceProcAddr( device, "vkCmdDrawIndirectCountAMD" ) );
        if ( !vkCmdDrawIndirectCount )
          vkCmdDrawIndirectCount = vkCmdDrawIndirectCountAMD;
        vkCmdDrawIndexedIndirectCountAMD = PFN_vkCmdDrawIndexedIndirectCountAMD( vkGetDeviceProcAddr( device, "vkCmdDrawIndexedIndirectCountAMD" ) );
        if ( !vkCmdDrawIndexedIndirectCount )
          vkCmdDrawIndexedIndirectCount = vkCmdDrawIndexedIndirectCountAMD;

        //=== VK_AMD_shader_info ===
        vkGetShaderInfoAMD = PFN_vkGetShaderInfoAMD( vkGetDeviceProcAddr( device, "vkGetShaderInfoAMD" ) );

        //=== VK_KHR_dynamic_rendering ===
        vkCmdBeginRenderingKHR = PFN_vkCmdBeginRenderingKHR( vkGetDeviceProcAddr( device, "vkCmdBeginRenderingKHR" ) );
        if ( !vkCmdBeginRendering )
          vkCmdBeginRendering = vkCmdBeginRenderingKHR;
        vkCmdEndRenderingKHR = PFN_vkCmdEndRenderingKHR( vkGetDeviceProcAddr( device, "vkCmdEndRenderingKHR" ) );
        if ( !vkCmdEndRendering )
          vkCmdEndRendering = vkCmdEndRenderingKHR;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_NV_external_memory_win32 ===
        vkGetMemoryWin32HandleNV = PFN_vkGetMemoryWin32HandleNV( vkGetDeviceProcAddr( device, "vkGetMemoryWin32HandleNV" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_device_group ===
        vkGetDeviceGroupPeerMemoryFeaturesKHR =
          PFN_vkGetDeviceGroupPeerMemoryFeaturesKHR( vkGetDeviceProcAddr( device, "vkGetDeviceGroupPeerMemoryFeaturesKHR" ) );
        if ( !vkGetDeviceGroupPeerMemoryFeatures )
          vkGetDeviceGroupPeerMemoryFeatures = vkGetDeviceGroupPeerMemoryFeaturesKHR;
        vkCmdSetDeviceMaskKHR = PFN_vkCmdSetDeviceMaskKHR( vkGetDeviceProcAddr( device, "vkCmdSetDeviceMaskKHR" ) );
        if ( !vkCmdSetDeviceMask )
          vkCmdSetDeviceMask = vkCmdSetDeviceMaskKHR;
        vkCmdDispatchBaseKHR = PFN_vkCmdDispatchBaseKHR( vkGetDeviceProcAddr( device, "vkCmdDispatchBaseKHR" ) );
        if ( !vkCmdDispatchBase )
          vkCmdDispatchBase = vkCmdDispatchBaseKHR;

        //=== VK_KHR_maintenance1 ===
        vkTrimCommandPoolKHR = PFN_vkTrimCommandPoolKHR( vkGetDeviceProcAddr( device, "vkTrimCommandPoolKHR" ) );
        if ( !vkTrimCommandPool )
          vkTrimCommandPool = vkTrimCommandPoolKHR;

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_external_memory_win32 ===
        vkGetMemoryWin32HandleKHR           = PFN_vkGetMemoryWin32HandleKHR( vkGetDeviceProcAddr( device, "vkGetMemoryWin32HandleKHR" ) );
        vkGetMemoryWin32HandlePropertiesKHR = PFN_vkGetMemoryWin32HandlePropertiesKHR( vkGetDeviceProcAddr( device, "vkGetMemoryWin32HandlePropertiesKHR" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_external_memory_fd ===
        vkGetMemoryFdKHR           = PFN_vkGetMemoryFdKHR( vkGetDeviceProcAddr( device, "vkGetMemoryFdKHR" ) );
        vkGetMemoryFdPropertiesKHR = PFN_vkGetMemoryFdPropertiesKHR( vkGetDeviceProcAddr( device, "vkGetMemoryFdPropertiesKHR" ) );

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_external_semaphore_win32 ===
        vkImportSemaphoreWin32HandleKHR = PFN_vkImportSemaphoreWin32HandleKHR( vkGetDeviceProcAddr( device, "vkImportSemaphoreWin32HandleKHR" ) );
        vkGetSemaphoreWin32HandleKHR    = PFN_vkGetSemaphoreWin32HandleKHR( vkGetDeviceProcAddr( device, "vkGetSemaphoreWin32HandleKHR" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_external_semaphore_fd ===
        vkImportSemaphoreFdKHR = PFN_vkImportSemaphoreFdKHR( vkGetDeviceProcAddr( device, "vkImportSemaphoreFdKHR" ) );
        vkGetSemaphoreFdKHR    = PFN_vkGetSemaphoreFdKHR( vkGetDeviceProcAddr( device, "vkGetSemaphoreFdKHR" ) );

        //=== VK_KHR_push_descriptor ===
        vkCmdPushDescriptorSetKHR = PFN_vkCmdPushDescriptorSetKHR( vkGetDeviceProcAddr( device, "vkCmdPushDescriptorSetKHR" ) );
        if ( !vkCmdPushDescriptorSet )
          vkCmdPushDescriptorSet = vkCmdPushDescriptorSetKHR;
        vkCmdPushDescriptorSetWithTemplateKHR =
          PFN_vkCmdPushDescriptorSetWithTemplateKHR( vkGetDeviceProcAddr( device, "vkCmdPushDescriptorSetWithTemplateKHR" ) );
        if ( !vkCmdPushDescriptorSetWithTemplate )
          vkCmdPushDescriptorSetWithTemplate = vkCmdPushDescriptorSetWithTemplateKHR;

        //=== VK_EXT_conditional_rendering ===
        vkCmdBeginConditionalRenderingEXT = PFN_vkCmdBeginConditionalRenderingEXT( vkGetDeviceProcAddr( device, "vkCmdBeginConditionalRenderingEXT" ) );
        vkCmdEndConditionalRenderingEXT   = PFN_vkCmdEndConditionalRenderingEXT( vkGetDeviceProcAddr( device, "vkCmdEndConditionalRenderingEXT" ) );

        //=== VK_KHR_descriptor_update_template ===
        vkCreateDescriptorUpdateTemplateKHR = PFN_vkCreateDescriptorUpdateTemplateKHR( vkGetDeviceProcAddr( device, "vkCreateDescriptorUpdateTemplateKHR" ) );
        if ( !vkCreateDescriptorUpdateTemplate )
          vkCreateDescriptorUpdateTemplate = vkCreateDescriptorUpdateTemplateKHR;
        vkDestroyDescriptorUpdateTemplateKHR =
          PFN_vkDestroyDescriptorUpdateTemplateKHR( vkGetDeviceProcAddr( device, "vkDestroyDescriptorUpdateTemplateKHR" ) );
        if ( !vkDestroyDescriptorUpdateTemplate )
          vkDestroyDescriptorUpdateTemplate = vkDestroyDescriptorUpdateTemplateKHR;
        vkUpdateDescriptorSetWithTemplateKHR =
          PFN_vkUpdateDescriptorSetWithTemplateKHR( vkGetDeviceProcAddr( device, "vkUpdateDescriptorSetWithTemplateKHR" ) );
        if ( !vkUpdateDescriptorSetWithTemplate )
          vkUpdateDescriptorSetWithTemplate = vkUpdateDescriptorSetWithTemplateKHR;

        //=== VK_NV_clip_space_w_scaling ===
        vkCmdSetViewportWScalingNV = PFN_vkCmdSetViewportWScalingNV( vkGetDeviceProcAddr( device, "vkCmdSetViewportWScalingNV" ) );

        //=== VK_EXT_display_control ===
        vkDisplayPowerControlEXT  = PFN_vkDisplayPowerControlEXT( vkGetDeviceProcAddr( device, "vkDisplayPowerControlEXT" ) );
        vkRegisterDeviceEventEXT  = PFN_vkRegisterDeviceEventEXT( vkGetDeviceProcAddr( device, "vkRegisterDeviceEventEXT" ) );
        vkRegisterDisplayEventEXT = PFN_vkRegisterDisplayEventEXT( vkGetDeviceProcAddr( device, "vkRegisterDisplayEventEXT" ) );
        vkGetSwapchainCounterEXT  = PFN_vkGetSwapchainCounterEXT( vkGetDeviceProcAddr( device, "vkGetSwapchainCounterEXT" ) );

        //=== VK_GOOGLE_display_timing ===
        vkGetRefreshCycleDurationGOOGLE   = PFN_vkGetRefreshCycleDurationGOOGLE( vkGetDeviceProcAddr( device, "vkGetRefreshCycleDurationGOOGLE" ) );
        vkGetPastPresentationTimingGOOGLE = PFN_vkGetPastPresentationTimingGOOGLE( vkGetDeviceProcAddr( device, "vkGetPastPresentationTimingGOOGLE" ) );

        //=== VK_EXT_discard_rectangles ===
        vkCmdSetDiscardRectangleEXT       = PFN_vkCmdSetDiscardRectangleEXT( vkGetDeviceProcAddr( device, "vkCmdSetDiscardRectangleEXT" ) );
        vkCmdSetDiscardRectangleEnableEXT = PFN_vkCmdSetDiscardRectangleEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDiscardRectangleEnableEXT" ) );
        vkCmdSetDiscardRectangleModeEXT   = PFN_vkCmdSetDiscardRectangleModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetDiscardRectangleModeEXT" ) );

        //=== VK_EXT_hdr_metadata ===
        vkSetHdrMetadataEXT = PFN_vkSetHdrMetadataEXT( vkGetDeviceProcAddr( device, "vkSetHdrMetadataEXT" ) );

        //=== VK_KHR_create_renderpass2 ===
        vkCreateRenderPass2KHR = PFN_vkCreateRenderPass2KHR( vkGetDeviceProcAddr( device, "vkCreateRenderPass2KHR" ) );
        if ( !vkCreateRenderPass2 )
          vkCreateRenderPass2 = vkCreateRenderPass2KHR;
        vkCmdBeginRenderPass2KHR = PFN_vkCmdBeginRenderPass2KHR( vkGetDeviceProcAddr( device, "vkCmdBeginRenderPass2KHR" ) );
        if ( !vkCmdBeginRenderPass2 )
          vkCmdBeginRenderPass2 = vkCmdBeginRenderPass2KHR;
        vkCmdNextSubpass2KHR = PFN_vkCmdNextSubpass2KHR( vkGetDeviceProcAddr( device, "vkCmdNextSubpass2KHR" ) );
        if ( !vkCmdNextSubpass2 )
          vkCmdNextSubpass2 = vkCmdNextSubpass2KHR;
        vkCmdEndRenderPass2KHR = PFN_vkCmdEndRenderPass2KHR( vkGetDeviceProcAddr( device, "vkCmdEndRenderPass2KHR" ) );
        if ( !vkCmdEndRenderPass2 )
          vkCmdEndRenderPass2 = vkCmdEndRenderPass2KHR;

        //=== VK_KHR_shared_presentable_image ===
        vkGetSwapchainStatusKHR = PFN_vkGetSwapchainStatusKHR( vkGetDeviceProcAddr( device, "vkGetSwapchainStatusKHR" ) );

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_KHR_external_fence_win32 ===
        vkImportFenceWin32HandleKHR = PFN_vkImportFenceWin32HandleKHR( vkGetDeviceProcAddr( device, "vkImportFenceWin32HandleKHR" ) );
        vkGetFenceWin32HandleKHR    = PFN_vkGetFenceWin32HandleKHR( vkGetDeviceProcAddr( device, "vkGetFenceWin32HandleKHR" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_external_fence_fd ===
        vkImportFenceFdKHR = PFN_vkImportFenceFdKHR( vkGetDeviceProcAddr( device, "vkImportFenceFdKHR" ) );
        vkGetFenceFdKHR    = PFN_vkGetFenceFdKHR( vkGetDeviceProcAddr( device, "vkGetFenceFdKHR" ) );

        //=== VK_KHR_performance_query ===
        vkAcquireProfilingLockKHR = PFN_vkAcquireProfilingLockKHR( vkGetDeviceProcAddr( device, "vkAcquireProfilingLockKHR" ) );
        vkReleaseProfilingLockKHR = PFN_vkReleaseProfilingLockKHR( vkGetDeviceProcAddr( device, "vkReleaseProfilingLockKHR" ) );

        //=== VK_EXT_debug_utils ===
        vkSetDebugUtilsObjectNameEXT    = PFN_vkSetDebugUtilsObjectNameEXT( vkGetDeviceProcAddr( device, "vkSetDebugUtilsObjectNameEXT" ) );
        vkSetDebugUtilsObjectTagEXT     = PFN_vkSetDebugUtilsObjectTagEXT( vkGetDeviceProcAddr( device, "vkSetDebugUtilsObjectTagEXT" ) );
        vkQueueBeginDebugUtilsLabelEXT  = PFN_vkQueueBeginDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkQueueBeginDebugUtilsLabelEXT" ) );
        vkQueueEndDebugUtilsLabelEXT    = PFN_vkQueueEndDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkQueueEndDebugUtilsLabelEXT" ) );
        vkQueueInsertDebugUtilsLabelEXT = PFN_vkQueueInsertDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkQueueInsertDebugUtilsLabelEXT" ) );
        vkCmdBeginDebugUtilsLabelEXT    = PFN_vkCmdBeginDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkCmdBeginDebugUtilsLabelEXT" ) );
        vkCmdEndDebugUtilsLabelEXT      = PFN_vkCmdEndDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkCmdEndDebugUtilsLabelEXT" ) );
        vkCmdInsertDebugUtilsLabelEXT   = PFN_vkCmdInsertDebugUtilsLabelEXT( vkGetDeviceProcAddr( device, "vkCmdInsertDebugUtilsLabelEXT" ) );

#if defined( VK_USE_PLATFORM_ANDROID_KHR )
        //=== VK_ANDROID_external_memory_android_hardware_buffer ===
        vkGetAndroidHardwareBufferPropertiesANDROID =
          PFN_vkGetAndroidHardwareBufferPropertiesANDROID( vkGetDeviceProcAddr( device, "vkGetAndroidHardwareBufferPropertiesANDROID" ) );
        vkGetMemoryAndroidHardwareBufferANDROID =
          PFN_vkGetMemoryAndroidHardwareBufferANDROID( vkGetDeviceProcAddr( device, "vkGetMemoryAndroidHardwareBufferANDROID" ) );
#endif /*VK_USE_PLATFORM_ANDROID_KHR*/

        //=== VK_AMD_gpa_interface ===
        vkCreateGpaSessionAMD         = PFN_vkCreateGpaSessionAMD( vkGetDeviceProcAddr( device, "vkCreateGpaSessionAMD" ) );
        vkDestroyGpaSessionAMD        = PFN_vkDestroyGpaSessionAMD( vkGetDeviceProcAddr( device, "vkDestroyGpaSessionAMD" ) );
        vkSetGpaDeviceClockModeAMD    = PFN_vkSetGpaDeviceClockModeAMD( vkGetDeviceProcAddr( device, "vkSetGpaDeviceClockModeAMD" ) );
        vkGetGpaDeviceClockInfoAMD    = PFN_vkGetGpaDeviceClockInfoAMD( vkGetDeviceProcAddr( device, "vkGetGpaDeviceClockInfoAMD" ) );
        vkCmdBeginGpaSessionAMD       = PFN_vkCmdBeginGpaSessionAMD( vkGetDeviceProcAddr( device, "vkCmdBeginGpaSessionAMD" ) );
        vkCmdEndGpaSessionAMD         = PFN_vkCmdEndGpaSessionAMD( vkGetDeviceProcAddr( device, "vkCmdEndGpaSessionAMD" ) );
        vkCmdBeginGpaSampleAMD        = PFN_vkCmdBeginGpaSampleAMD( vkGetDeviceProcAddr( device, "vkCmdBeginGpaSampleAMD" ) );
        vkCmdEndGpaSampleAMD          = PFN_vkCmdEndGpaSampleAMD( vkGetDeviceProcAddr( device, "vkCmdEndGpaSampleAMD" ) );
        vkGetGpaSessionStatusAMD      = PFN_vkGetGpaSessionStatusAMD( vkGetDeviceProcAddr( device, "vkGetGpaSessionStatusAMD" ) );
        vkGetGpaSessionResultsAMD     = PFN_vkGetGpaSessionResultsAMD( vkGetDeviceProcAddr( device, "vkGetGpaSessionResultsAMD" ) );
        vkResetGpaSessionAMD          = PFN_vkResetGpaSessionAMD( vkGetDeviceProcAddr( device, "vkResetGpaSessionAMD" ) );
        vkCmdCopyGpaSessionResultsAMD = PFN_vkCmdCopyGpaSessionResultsAMD( vkGetDeviceProcAddr( device, "vkCmdCopyGpaSessionResultsAMD" ) );

#if defined( VK_ENABLE_BETA_EXTENSIONS )
        //=== VK_AMDX_shader_enqueue ===
        vkCreateExecutionGraphPipelinesAMDX = PFN_vkCreateExecutionGraphPipelinesAMDX( vkGetDeviceProcAddr( device, "vkCreateExecutionGraphPipelinesAMDX" ) );
        vkGetExecutionGraphPipelineScratchSizeAMDX =
          PFN_vkGetExecutionGraphPipelineScratchSizeAMDX( vkGetDeviceProcAddr( device, "vkGetExecutionGraphPipelineScratchSizeAMDX" ) );
        vkGetExecutionGraphPipelineNodeIndexAMDX =
          PFN_vkGetExecutionGraphPipelineNodeIndexAMDX( vkGetDeviceProcAddr( device, "vkGetExecutionGraphPipelineNodeIndexAMDX" ) );
        vkCmdInitializeGraphScratchMemoryAMDX =
          PFN_vkCmdInitializeGraphScratchMemoryAMDX( vkGetDeviceProcAddr( device, "vkCmdInitializeGraphScratchMemoryAMDX" ) );
        vkCmdDispatchGraphAMDX              = PFN_vkCmdDispatchGraphAMDX( vkGetDeviceProcAddr( device, "vkCmdDispatchGraphAMDX" ) );
        vkCmdDispatchGraphIndirectAMDX      = PFN_vkCmdDispatchGraphIndirectAMDX( vkGetDeviceProcAddr( device, "vkCmdDispatchGraphIndirectAMDX" ) );
        vkCmdDispatchGraphIndirectCountAMDX = PFN_vkCmdDispatchGraphIndirectCountAMDX( vkGetDeviceProcAddr( device, "vkCmdDispatchGraphIndirectCountAMDX" ) );
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

        //=== VK_EXT_descriptor_heap ===
        vkWriteSamplerDescriptorsEXT     = PFN_vkWriteSamplerDescriptorsEXT( vkGetDeviceProcAddr( device, "vkWriteSamplerDescriptorsEXT" ) );
        vkWriteResourceDescriptorsEXT    = PFN_vkWriteResourceDescriptorsEXT( vkGetDeviceProcAddr( device, "vkWriteResourceDescriptorsEXT" ) );
        vkCmdBindSamplerHeapEXT          = PFN_vkCmdBindSamplerHeapEXT( vkGetDeviceProcAddr( device, "vkCmdBindSamplerHeapEXT" ) );
        vkCmdBindResourceHeapEXT         = PFN_vkCmdBindResourceHeapEXT( vkGetDeviceProcAddr( device, "vkCmdBindResourceHeapEXT" ) );
        vkCmdPushDataEXT                 = PFN_vkCmdPushDataEXT( vkGetDeviceProcAddr( device, "vkCmdPushDataEXT" ) );
        vkGetImageOpaqueCaptureDataEXT   = PFN_vkGetImageOpaqueCaptureDataEXT( vkGetDeviceProcAddr( device, "vkGetImageOpaqueCaptureDataEXT" ) );
        vkRegisterCustomBorderColorEXT   = PFN_vkRegisterCustomBorderColorEXT( vkGetDeviceProcAddr( device, "vkRegisterCustomBorderColorEXT" ) );
        vkUnregisterCustomBorderColorEXT = PFN_vkUnregisterCustomBorderColorEXT( vkGetDeviceProcAddr( device, "vkUnregisterCustomBorderColorEXT" ) );
        vkGetTensorOpaqueCaptureDataARM  = PFN_vkGetTensorOpaqueCaptureDataARM( vkGetDeviceProcAddr( device, "vkGetTensorOpaqueCaptureDataARM" ) );

        //=== VK_EXT_sample_locations ===
        vkCmdSetSampleLocationsEXT = PFN_vkCmdSetSampleLocationsEXT( vkGetDeviceProcAddr( device, "vkCmdSetSampleLocationsEXT" ) );

        //=== VK_KHR_get_memory_requirements2 ===
        vkGetImageMemoryRequirements2KHR = PFN_vkGetImageMemoryRequirements2KHR( vkGetDeviceProcAddr( device, "vkGetImageMemoryRequirements2KHR" ) );
        if ( !vkGetImageMemoryRequirements2 )
          vkGetImageMemoryRequirements2 = vkGetImageMemoryRequirements2KHR;
        vkGetBufferMemoryRequirements2KHR = PFN_vkGetBufferMemoryRequirements2KHR( vkGetDeviceProcAddr( device, "vkGetBufferMemoryRequirements2KHR" ) );
        if ( !vkGetBufferMemoryRequirements2 )
          vkGetBufferMemoryRequirements2 = vkGetBufferMemoryRequirements2KHR;
        vkGetImageSparseMemoryRequirements2KHR =
          PFN_vkGetImageSparseMemoryRequirements2KHR( vkGetDeviceProcAddr( device, "vkGetImageSparseMemoryRequirements2KHR" ) );
        if ( !vkGetImageSparseMemoryRequirements2 )
          vkGetImageSparseMemoryRequirements2 = vkGetImageSparseMemoryRequirements2KHR;

        //=== VK_KHR_acceleration_structure ===
        vkCreateAccelerationStructureKHR    = PFN_vkCreateAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkCreateAccelerationStructureKHR" ) );
        vkDestroyAccelerationStructureKHR   = PFN_vkDestroyAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkDestroyAccelerationStructureKHR" ) );
        vkCmdBuildAccelerationStructuresKHR = PFN_vkCmdBuildAccelerationStructuresKHR( vkGetDeviceProcAddr( device, "vkCmdBuildAccelerationStructuresKHR" ) );
        vkCmdBuildAccelerationStructuresIndirectKHR =
          PFN_vkCmdBuildAccelerationStructuresIndirectKHR( vkGetDeviceProcAddr( device, "vkCmdBuildAccelerationStructuresIndirectKHR" ) );
        vkBuildAccelerationStructuresKHR = PFN_vkBuildAccelerationStructuresKHR( vkGetDeviceProcAddr( device, "vkBuildAccelerationStructuresKHR" ) );
        vkCopyAccelerationStructureKHR   = PFN_vkCopyAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkCopyAccelerationStructureKHR" ) );
        vkCopyAccelerationStructureToMemoryKHR =
          PFN_vkCopyAccelerationStructureToMemoryKHR( vkGetDeviceProcAddr( device, "vkCopyAccelerationStructureToMemoryKHR" ) );
        vkCopyMemoryToAccelerationStructureKHR =
          PFN_vkCopyMemoryToAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkCopyMemoryToAccelerationStructureKHR" ) );
        vkWriteAccelerationStructuresPropertiesKHR =
          PFN_vkWriteAccelerationStructuresPropertiesKHR( vkGetDeviceProcAddr( device, "vkWriteAccelerationStructuresPropertiesKHR" ) );
        vkCmdCopyAccelerationStructureKHR = PFN_vkCmdCopyAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkCmdCopyAccelerationStructureKHR" ) );
        vkCmdCopyAccelerationStructureToMemoryKHR =
          PFN_vkCmdCopyAccelerationStructureToMemoryKHR( vkGetDeviceProcAddr( device, "vkCmdCopyAccelerationStructureToMemoryKHR" ) );
        vkCmdCopyMemoryToAccelerationStructureKHR =
          PFN_vkCmdCopyMemoryToAccelerationStructureKHR( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryToAccelerationStructureKHR" ) );
        vkGetAccelerationStructureDeviceAddressKHR =
          PFN_vkGetAccelerationStructureDeviceAddressKHR( vkGetDeviceProcAddr( device, "vkGetAccelerationStructureDeviceAddressKHR" ) );
        vkCmdWriteAccelerationStructuresPropertiesKHR =
          PFN_vkCmdWriteAccelerationStructuresPropertiesKHR( vkGetDeviceProcAddr( device, "vkCmdWriteAccelerationStructuresPropertiesKHR" ) );
        vkGetDeviceAccelerationStructureCompatibilityKHR =
          PFN_vkGetDeviceAccelerationStructureCompatibilityKHR( vkGetDeviceProcAddr( device, "vkGetDeviceAccelerationStructureCompatibilityKHR" ) );
        vkGetAccelerationStructureBuildSizesKHR =
          PFN_vkGetAccelerationStructureBuildSizesKHR( vkGetDeviceProcAddr( device, "vkGetAccelerationStructureBuildSizesKHR" ) );

        //=== VK_KHR_ray_tracing_pipeline ===
        vkCmdTraceRaysKHR              = PFN_vkCmdTraceRaysKHR( vkGetDeviceProcAddr( device, "vkCmdTraceRaysKHR" ) );
        vkCreateRayTracingPipelinesKHR = PFN_vkCreateRayTracingPipelinesKHR( vkGetDeviceProcAddr( device, "vkCreateRayTracingPipelinesKHR" ) );
        vkGetRayTracingShaderGroupHandlesKHR =
          PFN_vkGetRayTracingShaderGroupHandlesKHR( vkGetDeviceProcAddr( device, "vkGetRayTracingShaderGroupHandlesKHR" ) );
        vkGetRayTracingCaptureReplayShaderGroupHandlesKHR =
          PFN_vkGetRayTracingCaptureReplayShaderGroupHandlesKHR( vkGetDeviceProcAddr( device, "vkGetRayTracingCaptureReplayShaderGroupHandlesKHR" ) );
        vkCmdTraceRaysIndirectKHR = PFN_vkCmdTraceRaysIndirectKHR( vkGetDeviceProcAddr( device, "vkCmdTraceRaysIndirectKHR" ) );
        vkGetRayTracingShaderGroupStackSizeKHR =
          PFN_vkGetRayTracingShaderGroupStackSizeKHR( vkGetDeviceProcAddr( device, "vkGetRayTracingShaderGroupStackSizeKHR" ) );
        vkCmdSetRayTracingPipelineStackSizeKHR =
          PFN_vkCmdSetRayTracingPipelineStackSizeKHR( vkGetDeviceProcAddr( device, "vkCmdSetRayTracingPipelineStackSizeKHR" ) );

        //=== VK_KHR_sampler_ycbcr_conversion ===
        vkCreateSamplerYcbcrConversionKHR = PFN_vkCreateSamplerYcbcrConversionKHR( vkGetDeviceProcAddr( device, "vkCreateSamplerYcbcrConversionKHR" ) );
        if ( !vkCreateSamplerYcbcrConversion )
          vkCreateSamplerYcbcrConversion = vkCreateSamplerYcbcrConversionKHR;
        vkDestroySamplerYcbcrConversionKHR = PFN_vkDestroySamplerYcbcrConversionKHR( vkGetDeviceProcAddr( device, "vkDestroySamplerYcbcrConversionKHR" ) );
        if ( !vkDestroySamplerYcbcrConversion )
          vkDestroySamplerYcbcrConversion = vkDestroySamplerYcbcrConversionKHR;

        //=== VK_KHR_bind_memory2 ===
        vkBindBufferMemory2KHR = PFN_vkBindBufferMemory2KHR( vkGetDeviceProcAddr( device, "vkBindBufferMemory2KHR" ) );
        if ( !vkBindBufferMemory2 )
          vkBindBufferMemory2 = vkBindBufferMemory2KHR;
        vkBindImageMemory2KHR = PFN_vkBindImageMemory2KHR( vkGetDeviceProcAddr( device, "vkBindImageMemory2KHR" ) );
        if ( !vkBindImageMemory2 )
          vkBindImageMemory2 = vkBindImageMemory2KHR;

        //=== VK_EXT_image_drm_format_modifier ===
        vkGetImageDrmFormatModifierPropertiesEXT =
          PFN_vkGetImageDrmFormatModifierPropertiesEXT( vkGetDeviceProcAddr( device, "vkGetImageDrmFormatModifierPropertiesEXT" ) );

        //=== VK_EXT_validation_cache ===
        vkCreateValidationCacheEXT  = PFN_vkCreateValidationCacheEXT( vkGetDeviceProcAddr( device, "vkCreateValidationCacheEXT" ) );
        vkDestroyValidationCacheEXT = PFN_vkDestroyValidationCacheEXT( vkGetDeviceProcAddr( device, "vkDestroyValidationCacheEXT" ) );
        vkMergeValidationCachesEXT  = PFN_vkMergeValidationCachesEXT( vkGetDeviceProcAddr( device, "vkMergeValidationCachesEXT" ) );
        vkGetValidationCacheDataEXT = PFN_vkGetValidationCacheDataEXT( vkGetDeviceProcAddr( device, "vkGetValidationCacheDataEXT" ) );

        //=== VK_NV_shading_rate_image ===
        vkCmdBindShadingRateImageNV = PFN_vkCmdBindShadingRateImageNV( vkGetDeviceProcAddr( device, "vkCmdBindShadingRateImageNV" ) );
        vkCmdSetViewportShadingRatePaletteNV =
          PFN_vkCmdSetViewportShadingRatePaletteNV( vkGetDeviceProcAddr( device, "vkCmdSetViewportShadingRatePaletteNV" ) );
        vkCmdSetCoarseSampleOrderNV = PFN_vkCmdSetCoarseSampleOrderNV( vkGetDeviceProcAddr( device, "vkCmdSetCoarseSampleOrderNV" ) );

        //=== VK_NV_ray_tracing ===
        vkCreateAccelerationStructureNV  = PFN_vkCreateAccelerationStructureNV( vkGetDeviceProcAddr( device, "vkCreateAccelerationStructureNV" ) );
        vkDestroyAccelerationStructureNV = PFN_vkDestroyAccelerationStructureNV( vkGetDeviceProcAddr( device, "vkDestroyAccelerationStructureNV" ) );
        vkGetAccelerationStructureMemoryRequirementsNV =
          PFN_vkGetAccelerationStructureMemoryRequirementsNV( vkGetDeviceProcAddr( device, "vkGetAccelerationStructureMemoryRequirementsNV" ) );
        vkBindAccelerationStructureMemoryNV = PFN_vkBindAccelerationStructureMemoryNV( vkGetDeviceProcAddr( device, "vkBindAccelerationStructureMemoryNV" ) );
        vkCmdBuildAccelerationStructureNV   = PFN_vkCmdBuildAccelerationStructureNV( vkGetDeviceProcAddr( device, "vkCmdBuildAccelerationStructureNV" ) );
        vkCmdCopyAccelerationStructureNV    = PFN_vkCmdCopyAccelerationStructureNV( vkGetDeviceProcAddr( device, "vkCmdCopyAccelerationStructureNV" ) );
        vkCmdTraceRaysNV                    = PFN_vkCmdTraceRaysNV( vkGetDeviceProcAddr( device, "vkCmdTraceRaysNV" ) );
        vkCreateRayTracingPipelinesNV       = PFN_vkCreateRayTracingPipelinesNV( vkGetDeviceProcAddr( device, "vkCreateRayTracingPipelinesNV" ) );
        vkGetRayTracingShaderGroupHandlesNV = PFN_vkGetRayTracingShaderGroupHandlesNV( vkGetDeviceProcAddr( device, "vkGetRayTracingShaderGroupHandlesNV" ) );
        if ( !vkGetRayTracingShaderGroupHandlesKHR )
          vkGetRayTracingShaderGroupHandlesKHR = vkGetRayTracingShaderGroupHandlesNV;
        vkGetAccelerationStructureHandleNV = PFN_vkGetAccelerationStructureHandleNV( vkGetDeviceProcAddr( device, "vkGetAccelerationStructureHandleNV" ) );
        vkCmdWriteAccelerationStructuresPropertiesNV =
          PFN_vkCmdWriteAccelerationStructuresPropertiesNV( vkGetDeviceProcAddr( device, "vkCmdWriteAccelerationStructuresPropertiesNV" ) );
        vkCompileDeferredNV = PFN_vkCompileDeferredNV( vkGetDeviceProcAddr( device, "vkCompileDeferredNV" ) );

        //=== VK_KHR_maintenance3 ===
        vkGetDescriptorSetLayoutSupportKHR = PFN_vkGetDescriptorSetLayoutSupportKHR( vkGetDeviceProcAddr( device, "vkGetDescriptorSetLayoutSupportKHR" ) );
        if ( !vkGetDescriptorSetLayoutSupport )
          vkGetDescriptorSetLayoutSupport = vkGetDescriptorSetLayoutSupportKHR;

        //=== VK_KHR_draw_indirect_count ===
        vkCmdDrawIndirectCountKHR = PFN_vkCmdDrawIndirectCountKHR( vkGetDeviceProcAddr( device, "vkCmdDrawIndirectCountKHR" ) );
        if ( !vkCmdDrawIndirectCount )
          vkCmdDrawIndirectCount = vkCmdDrawIndirectCountKHR;
        vkCmdDrawIndexedIndirectCountKHR = PFN_vkCmdDrawIndexedIndirectCountKHR( vkGetDeviceProcAddr( device, "vkCmdDrawIndexedIndirectCountKHR" ) );
        if ( !vkCmdDrawIndexedIndirectCount )
          vkCmdDrawIndexedIndirectCount = vkCmdDrawIndexedIndirectCountKHR;

        //=== VK_EXT_external_memory_host ===
        vkGetMemoryHostPointerPropertiesEXT = PFN_vkGetMemoryHostPointerPropertiesEXT( vkGetDeviceProcAddr( device, "vkGetMemoryHostPointerPropertiesEXT" ) );

        //=== VK_AMD_buffer_marker ===
        vkCmdWriteBufferMarkerAMD  = PFN_vkCmdWriteBufferMarkerAMD( vkGetDeviceProcAddr( device, "vkCmdWriteBufferMarkerAMD" ) );
        vkCmdWriteBufferMarker2AMD = PFN_vkCmdWriteBufferMarker2AMD( vkGetDeviceProcAddr( device, "vkCmdWriteBufferMarker2AMD" ) );

        //=== VK_EXT_calibrated_timestamps ===
        vkGetCalibratedTimestampsEXT = PFN_vkGetCalibratedTimestampsEXT( vkGetDeviceProcAddr( device, "vkGetCalibratedTimestampsEXT" ) );
        if ( !vkGetCalibratedTimestampsKHR )
          vkGetCalibratedTimestampsKHR = vkGetCalibratedTimestampsEXT;

        //=== VK_NV_mesh_shader ===
        vkCmdDrawMeshTasksNV              = PFN_vkCmdDrawMeshTasksNV( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksNV" ) );
        vkCmdDrawMeshTasksIndirectNV      = PFN_vkCmdDrawMeshTasksIndirectNV( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksIndirectNV" ) );
        vkCmdDrawMeshTasksIndirectCountNV = PFN_vkCmdDrawMeshTasksIndirectCountNV( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksIndirectCountNV" ) );

        //=== VK_NV_scissor_exclusive ===
        vkCmdSetExclusiveScissorEnableNV = PFN_vkCmdSetExclusiveScissorEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetExclusiveScissorEnableNV" ) );
        vkCmdSetExclusiveScissorNV       = PFN_vkCmdSetExclusiveScissorNV( vkGetDeviceProcAddr( device, "vkCmdSetExclusiveScissorNV" ) );

        //=== VK_NV_device_diagnostic_checkpoints ===
        vkCmdSetCheckpointNV        = PFN_vkCmdSetCheckpointNV( vkGetDeviceProcAddr( device, "vkCmdSetCheckpointNV" ) );
        vkGetQueueCheckpointDataNV  = PFN_vkGetQueueCheckpointDataNV( vkGetDeviceProcAddr( device, "vkGetQueueCheckpointDataNV" ) );
        vkGetQueueCheckpointData2NV = PFN_vkGetQueueCheckpointData2NV( vkGetDeviceProcAddr( device, "vkGetQueueCheckpointData2NV" ) );

        //=== VK_KHR_timeline_semaphore ===
        vkGetSemaphoreCounterValueKHR = PFN_vkGetSemaphoreCounterValueKHR( vkGetDeviceProcAddr( device, "vkGetSemaphoreCounterValueKHR" ) );
        if ( !vkGetSemaphoreCounterValue )
          vkGetSemaphoreCounterValue = vkGetSemaphoreCounterValueKHR;
        vkWaitSemaphoresKHR = PFN_vkWaitSemaphoresKHR( vkGetDeviceProcAddr( device, "vkWaitSemaphoresKHR" ) );
        if ( !vkWaitSemaphores )
          vkWaitSemaphores = vkWaitSemaphoresKHR;
        vkSignalSemaphoreKHR = PFN_vkSignalSemaphoreKHR( vkGetDeviceProcAddr( device, "vkSignalSemaphoreKHR" ) );
        if ( !vkSignalSemaphore )
          vkSignalSemaphore = vkSignalSemaphoreKHR;

        //=== VK_EXT_present_timing ===
        vkSetSwapchainPresentTimingQueueSizeEXT =
          PFN_vkSetSwapchainPresentTimingQueueSizeEXT( vkGetDeviceProcAddr( device, "vkSetSwapchainPresentTimingQueueSizeEXT" ) );
        vkGetSwapchainTimingPropertiesEXT = PFN_vkGetSwapchainTimingPropertiesEXT( vkGetDeviceProcAddr( device, "vkGetSwapchainTimingPropertiesEXT" ) );
        vkGetSwapchainTimeDomainPropertiesEXT =
          PFN_vkGetSwapchainTimeDomainPropertiesEXT( vkGetDeviceProcAddr( device, "vkGetSwapchainTimeDomainPropertiesEXT" ) );
        vkGetPastPresentationTimingEXT = PFN_vkGetPastPresentationTimingEXT( vkGetDeviceProcAddr( device, "vkGetPastPresentationTimingEXT" ) );

        //=== VK_INTEL_performance_query ===
        vkInitializePerformanceApiINTEL   = PFN_vkInitializePerformanceApiINTEL( vkGetDeviceProcAddr( device, "vkInitializePerformanceApiINTEL" ) );
        vkUninitializePerformanceApiINTEL = PFN_vkUninitializePerformanceApiINTEL( vkGetDeviceProcAddr( device, "vkUninitializePerformanceApiINTEL" ) );
        vkCmdSetPerformanceMarkerINTEL    = PFN_vkCmdSetPerformanceMarkerINTEL( vkGetDeviceProcAddr( device, "vkCmdSetPerformanceMarkerINTEL" ) );
        vkCmdSetPerformanceStreamMarkerINTEL =
          PFN_vkCmdSetPerformanceStreamMarkerINTEL( vkGetDeviceProcAddr( device, "vkCmdSetPerformanceStreamMarkerINTEL" ) );
        vkCmdSetPerformanceOverrideINTEL = PFN_vkCmdSetPerformanceOverrideINTEL( vkGetDeviceProcAddr( device, "vkCmdSetPerformanceOverrideINTEL" ) );
        vkAcquirePerformanceConfigurationINTEL =
          PFN_vkAcquirePerformanceConfigurationINTEL( vkGetDeviceProcAddr( device, "vkAcquirePerformanceConfigurationINTEL" ) );
        vkReleasePerformanceConfigurationINTEL =
          PFN_vkReleasePerformanceConfigurationINTEL( vkGetDeviceProcAddr( device, "vkReleasePerformanceConfigurationINTEL" ) );
        vkQueueSetPerformanceConfigurationINTEL =
          PFN_vkQueueSetPerformanceConfigurationINTEL( vkGetDeviceProcAddr( device, "vkQueueSetPerformanceConfigurationINTEL" ) );
        vkGetPerformanceParameterINTEL = PFN_vkGetPerformanceParameterINTEL( vkGetDeviceProcAddr( device, "vkGetPerformanceParameterINTEL" ) );

        //=== VK_AMD_display_native_hdr ===
        vkSetLocalDimmingAMD = PFN_vkSetLocalDimmingAMD( vkGetDeviceProcAddr( device, "vkSetLocalDimmingAMD" ) );

        //=== VK_KHR_fragment_shading_rate ===
        vkCmdSetFragmentShadingRateKHR = PFN_vkCmdSetFragmentShadingRateKHR( vkGetDeviceProcAddr( device, "vkCmdSetFragmentShadingRateKHR" ) );

        //=== VK_KHR_dynamic_rendering_local_read ===
        vkCmdSetRenderingAttachmentLocationsKHR =
          PFN_vkCmdSetRenderingAttachmentLocationsKHR( vkGetDeviceProcAddr( device, "vkCmdSetRenderingAttachmentLocationsKHR" ) );
        if ( !vkCmdSetRenderingAttachmentLocations )
          vkCmdSetRenderingAttachmentLocations = vkCmdSetRenderingAttachmentLocationsKHR;
        vkCmdSetRenderingInputAttachmentIndicesKHR =
          PFN_vkCmdSetRenderingInputAttachmentIndicesKHR( vkGetDeviceProcAddr( device, "vkCmdSetRenderingInputAttachmentIndicesKHR" ) );
        if ( !vkCmdSetRenderingInputAttachmentIndices )
          vkCmdSetRenderingInputAttachmentIndices = vkCmdSetRenderingInputAttachmentIndicesKHR;

        //=== VK_EXT_buffer_device_address ===
        vkGetBufferDeviceAddressEXT = PFN_vkGetBufferDeviceAddressEXT( vkGetDeviceProcAddr( device, "vkGetBufferDeviceAddressEXT" ) );
        if ( !vkGetBufferDeviceAddress )
          vkGetBufferDeviceAddress = vkGetBufferDeviceAddressEXT;

        //=== VK_KHR_present_wait ===
        vkWaitForPresentKHR = PFN_vkWaitForPresentKHR( vkGetDeviceProcAddr( device, "vkWaitForPresentKHR" ) );

#if defined( VK_USE_PLATFORM_WIN32_KHR )
        //=== VK_EXT_full_screen_exclusive ===
        vkAcquireFullScreenExclusiveModeEXT = PFN_vkAcquireFullScreenExclusiveModeEXT( vkGetDeviceProcAddr( device, "vkAcquireFullScreenExclusiveModeEXT" ) );
        vkReleaseFullScreenExclusiveModeEXT = PFN_vkReleaseFullScreenExclusiveModeEXT( vkGetDeviceProcAddr( device, "vkReleaseFullScreenExclusiveModeEXT" ) );
        vkGetDeviceGroupSurfacePresentModes2EXT =
          PFN_vkGetDeviceGroupSurfacePresentModes2EXT( vkGetDeviceProcAddr( device, "vkGetDeviceGroupSurfacePresentModes2EXT" ) );
#endif /*VK_USE_PLATFORM_WIN32_KHR*/

        //=== VK_KHR_buffer_device_address ===
        vkGetBufferDeviceAddressKHR = PFN_vkGetBufferDeviceAddressKHR( vkGetDeviceProcAddr( device, "vkGetBufferDeviceAddressKHR" ) );
        if ( !vkGetBufferDeviceAddress )
          vkGetBufferDeviceAddress = vkGetBufferDeviceAddressKHR;
        vkGetBufferOpaqueCaptureAddressKHR = PFN_vkGetBufferOpaqueCaptureAddressKHR( vkGetDeviceProcAddr( device, "vkGetBufferOpaqueCaptureAddressKHR" ) );
        if ( !vkGetBufferOpaqueCaptureAddress )
          vkGetBufferOpaqueCaptureAddress = vkGetBufferOpaqueCaptureAddressKHR;
        vkGetDeviceMemoryOpaqueCaptureAddressKHR =
          PFN_vkGetDeviceMemoryOpaqueCaptureAddressKHR( vkGetDeviceProcAddr( device, "vkGetDeviceMemoryOpaqueCaptureAddressKHR" ) );
        if ( !vkGetDeviceMemoryOpaqueCaptureAddress )
          vkGetDeviceMemoryOpaqueCaptureAddress = vkGetDeviceMemoryOpaqueCaptureAddressKHR;

        //=== VK_EXT_line_rasterization ===
        vkCmdSetLineStippleEXT = PFN_vkCmdSetLineStippleEXT( vkGetDeviceProcAddr( device, "vkCmdSetLineStippleEXT" ) );
        if ( !vkCmdSetLineStipple )
          vkCmdSetLineStipple = vkCmdSetLineStippleEXT;

        //=== VK_EXT_host_query_reset ===
        vkResetQueryPoolEXT = PFN_vkResetQueryPoolEXT( vkGetDeviceProcAddr( device, "vkResetQueryPoolEXT" ) );
        if ( !vkResetQueryPool )
          vkResetQueryPool = vkResetQueryPoolEXT;

        //=== VK_EXT_extended_dynamic_state ===
        vkCmdSetCullModeEXT = PFN_vkCmdSetCullModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetCullModeEXT" ) );
        if ( !vkCmdSetCullMode )
          vkCmdSetCullMode = vkCmdSetCullModeEXT;
        vkCmdSetFrontFaceEXT = PFN_vkCmdSetFrontFaceEXT( vkGetDeviceProcAddr( device, "vkCmdSetFrontFaceEXT" ) );
        if ( !vkCmdSetFrontFace )
          vkCmdSetFrontFace = vkCmdSetFrontFaceEXT;
        vkCmdSetPrimitiveTopologyEXT = PFN_vkCmdSetPrimitiveTopologyEXT( vkGetDeviceProcAddr( device, "vkCmdSetPrimitiveTopologyEXT" ) );
        if ( !vkCmdSetPrimitiveTopology )
          vkCmdSetPrimitiveTopology = vkCmdSetPrimitiveTopologyEXT;
        vkCmdSetViewportWithCountEXT = PFN_vkCmdSetViewportWithCountEXT( vkGetDeviceProcAddr( device, "vkCmdSetViewportWithCountEXT" ) );
        if ( !vkCmdSetViewportWithCount )
          vkCmdSetViewportWithCount = vkCmdSetViewportWithCountEXT;
        vkCmdSetScissorWithCountEXT = PFN_vkCmdSetScissorWithCountEXT( vkGetDeviceProcAddr( device, "vkCmdSetScissorWithCountEXT" ) );
        if ( !vkCmdSetScissorWithCount )
          vkCmdSetScissorWithCount = vkCmdSetScissorWithCountEXT;
        vkCmdBindVertexBuffers2EXT = PFN_vkCmdBindVertexBuffers2EXT( vkGetDeviceProcAddr( device, "vkCmdBindVertexBuffers2EXT" ) );
        if ( !vkCmdBindVertexBuffers2 )
          vkCmdBindVertexBuffers2 = vkCmdBindVertexBuffers2EXT;
        vkCmdSetDepthTestEnableEXT = PFN_vkCmdSetDepthTestEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthTestEnableEXT" ) );
        if ( !vkCmdSetDepthTestEnable )
          vkCmdSetDepthTestEnable = vkCmdSetDepthTestEnableEXT;
        vkCmdSetDepthWriteEnableEXT = PFN_vkCmdSetDepthWriteEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthWriteEnableEXT" ) );
        if ( !vkCmdSetDepthWriteEnable )
          vkCmdSetDepthWriteEnable = vkCmdSetDepthWriteEnableEXT;
        vkCmdSetDepthCompareOpEXT = PFN_vkCmdSetDepthCompareOpEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthCompareOpEXT" ) );
        if ( !vkCmdSetDepthCompareOp )
          vkCmdSetDepthCompareOp = vkCmdSetDepthCompareOpEXT;
        vkCmdSetDepthBoundsTestEnableEXT = PFN_vkCmdSetDepthBoundsTestEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthBoundsTestEnableEXT" ) );
        if ( !vkCmdSetDepthBoundsTestEnable )
          vkCmdSetDepthBoundsTestEnable = vkCmdSetDepthBoundsTestEnableEXT;
        vkCmdSetStencilTestEnableEXT = PFN_vkCmdSetStencilTestEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetStencilTestEnableEXT" ) );
        if ( !vkCmdSetStencilTestEnable )
          vkCmdSetStencilTestEnable = vkCmdSetStencilTestEnableEXT;
        vkCmdSetStencilOpEXT = PFN_vkCmdSetStencilOpEXT( vkGetDeviceProcAddr( device, "vkCmdSetStencilOpEXT" ) );
        if ( !vkCmdSetStencilOp )
          vkCmdSetStencilOp = vkCmdSetStencilOpEXT;

        //=== VK_KHR_deferred_host_operations ===
        vkCreateDeferredOperationKHR  = PFN_vkCreateDeferredOperationKHR( vkGetDeviceProcAddr( device, "vkCreateDeferredOperationKHR" ) );
        vkDestroyDeferredOperationKHR = PFN_vkDestroyDeferredOperationKHR( vkGetDeviceProcAddr( device, "vkDestroyDeferredOperationKHR" ) );
        vkGetDeferredOperationMaxConcurrencyKHR =
          PFN_vkGetDeferredOperationMaxConcurrencyKHR( vkGetDeviceProcAddr( device, "vkGetDeferredOperationMaxConcurrencyKHR" ) );
        vkGetDeferredOperationResultKHR = PFN_vkGetDeferredOperationResultKHR( vkGetDeviceProcAddr( device, "vkGetDeferredOperationResultKHR" ) );
        vkDeferredOperationJoinKHR      = PFN_vkDeferredOperationJoinKHR( vkGetDeviceProcAddr( device, "vkDeferredOperationJoinKHR" ) );

        //=== VK_KHR_pipeline_executable_properties ===
        vkGetPipelineExecutablePropertiesKHR =
          PFN_vkGetPipelineExecutablePropertiesKHR( vkGetDeviceProcAddr( device, "vkGetPipelineExecutablePropertiesKHR" ) );
        vkGetPipelineExecutableStatisticsKHR =
          PFN_vkGetPipelineExecutableStatisticsKHR( vkGetDeviceProcAddr( device, "vkGetPipelineExecutableStatisticsKHR" ) );
        vkGetPipelineExecutableInternalRepresentationsKHR =
          PFN_vkGetPipelineExecutableInternalRepresentationsKHR( vkGetDeviceProcAddr( device, "vkGetPipelineExecutableInternalRepresentationsKHR" ) );

        //=== VK_EXT_host_image_copy ===
        vkCopyMemoryToImageEXT = PFN_vkCopyMemoryToImageEXT( vkGetDeviceProcAddr( device, "vkCopyMemoryToImageEXT" ) );
        if ( !vkCopyMemoryToImage )
          vkCopyMemoryToImage = vkCopyMemoryToImageEXT;
        vkCopyImageToMemoryEXT = PFN_vkCopyImageToMemoryEXT( vkGetDeviceProcAddr( device, "vkCopyImageToMemoryEXT" ) );
        if ( !vkCopyImageToMemory )
          vkCopyImageToMemory = vkCopyImageToMemoryEXT;
        vkCopyImageToImageEXT = PFN_vkCopyImageToImageEXT( vkGetDeviceProcAddr( device, "vkCopyImageToImageEXT" ) );
        if ( !vkCopyImageToImage )
          vkCopyImageToImage = vkCopyImageToImageEXT;
        vkTransitionImageLayoutEXT = PFN_vkTransitionImageLayoutEXT( vkGetDeviceProcAddr( device, "vkTransitionImageLayoutEXT" ) );
        if ( !vkTransitionImageLayout )
          vkTransitionImageLayout = vkTransitionImageLayoutEXT;
        vkGetImageSubresourceLayout2EXT = PFN_vkGetImageSubresourceLayout2EXT( vkGetDeviceProcAddr( device, "vkGetImageSubresourceLayout2EXT" ) );
        if ( !vkGetImageSubresourceLayout2 )
          vkGetImageSubresourceLayout2 = vkGetImageSubresourceLayout2EXT;

        //=== VK_KHR_map_memory2 ===
        vkMapMemory2KHR = PFN_vkMapMemory2KHR( vkGetDeviceProcAddr( device, "vkMapMemory2KHR" ) );
        if ( !vkMapMemory2 )
          vkMapMemory2 = vkMapMemory2KHR;
        vkUnmapMemory2KHR = PFN_vkUnmapMemory2KHR( vkGetDeviceProcAddr( device, "vkUnmapMemory2KHR" ) );
        if ( !vkUnmapMemory2 )
          vkUnmapMemory2 = vkUnmapMemory2KHR;

        //=== VK_EXT_swapchain_maintenance1 ===
        vkReleaseSwapchainImagesEXT = PFN_vkReleaseSwapchainImagesEXT( vkGetDeviceProcAddr( device, "vkReleaseSwapchainImagesEXT" ) );
        if ( !vkReleaseSwapchainImagesKHR )
          vkReleaseSwapchainImagesKHR = vkReleaseSwapchainImagesEXT;

        //=== VK_NV_device_generated_commands ===
        vkGetGeneratedCommandsMemoryRequirementsNV =
          PFN_vkGetGeneratedCommandsMemoryRequirementsNV( vkGetDeviceProcAddr( device, "vkGetGeneratedCommandsMemoryRequirementsNV" ) );
        vkCmdPreprocessGeneratedCommandsNV = PFN_vkCmdPreprocessGeneratedCommandsNV( vkGetDeviceProcAddr( device, "vkCmdPreprocessGeneratedCommandsNV" ) );
        vkCmdExecuteGeneratedCommandsNV    = PFN_vkCmdExecuteGeneratedCommandsNV( vkGetDeviceProcAddr( device, "vkCmdExecuteGeneratedCommandsNV" ) );
        vkCmdBindPipelineShaderGroupNV     = PFN_vkCmdBindPipelineShaderGroupNV( vkGetDeviceProcAddr( device, "vkCmdBindPipelineShaderGroupNV" ) );
        vkCreateIndirectCommandsLayoutNV   = PFN_vkCreateIndirectCommandsLayoutNV( vkGetDeviceProcAddr( device, "vkCreateIndirectCommandsLayoutNV" ) );
        vkDestroyIndirectCommandsLayoutNV  = PFN_vkDestroyIndirectCommandsLayoutNV( vkGetDeviceProcAddr( device, "vkDestroyIndirectCommandsLayoutNV" ) );

        //=== VK_EXT_depth_bias_control ===
        vkCmdSetDepthBias2EXT = PFN_vkCmdSetDepthBias2EXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthBias2EXT" ) );

        //=== VK_EXT_private_data ===
        vkCreatePrivateDataSlotEXT = PFN_vkCreatePrivateDataSlotEXT( vkGetDeviceProcAddr( device, "vkCreatePrivateDataSlotEXT" ) );
        if ( !vkCreatePrivateDataSlot )
          vkCreatePrivateDataSlot = vkCreatePrivateDataSlotEXT;
        vkDestroyPrivateDataSlotEXT = PFN_vkDestroyPrivateDataSlotEXT( vkGetDeviceProcAddr( device, "vkDestroyPrivateDataSlotEXT" ) );
        if ( !vkDestroyPrivateDataSlot )
          vkDestroyPrivateDataSlot = vkDestroyPrivateDataSlotEXT;
        vkSetPrivateDataEXT = PFN_vkSetPrivateDataEXT( vkGetDeviceProcAddr( device, "vkSetPrivateDataEXT" ) );
        if ( !vkSetPrivateData )
          vkSetPrivateData = vkSetPrivateDataEXT;
        vkGetPrivateDataEXT = PFN_vkGetPrivateDataEXT( vkGetDeviceProcAddr( device, "vkGetPrivateDataEXT" ) );
        if ( !vkGetPrivateData )
          vkGetPrivateData = vkGetPrivateDataEXT;

        //=== VK_KHR_video_encode_queue ===
        vkGetEncodedVideoSessionParametersKHR =
          PFN_vkGetEncodedVideoSessionParametersKHR( vkGetDeviceProcAddr( device, "vkGetEncodedVideoSessionParametersKHR" ) );
        vkCmdEncodeVideoKHR = PFN_vkCmdEncodeVideoKHR( vkGetDeviceProcAddr( device, "vkCmdEncodeVideoKHR" ) );

        //=== VK_QCOM_queue_perf_hint ===
        vkQueueSetPerfHintQCOM = PFN_vkQueueSetPerfHintQCOM( vkGetDeviceProcAddr( device, "vkQueueSetPerfHintQCOM" ) );

#if defined( VK_ENABLE_BETA_EXTENSIONS )
        //=== VK_NV_cuda_kernel_launch ===
        vkCreateCudaModuleNV    = PFN_vkCreateCudaModuleNV( vkGetDeviceProcAddr( device, "vkCreateCudaModuleNV" ) );
        vkGetCudaModuleCacheNV  = PFN_vkGetCudaModuleCacheNV( vkGetDeviceProcAddr( device, "vkGetCudaModuleCacheNV" ) );
        vkCreateCudaFunctionNV  = PFN_vkCreateCudaFunctionNV( vkGetDeviceProcAddr( device, "vkCreateCudaFunctionNV" ) );
        vkDestroyCudaModuleNV   = PFN_vkDestroyCudaModuleNV( vkGetDeviceProcAddr( device, "vkDestroyCudaModuleNV" ) );
        vkDestroyCudaFunctionNV = PFN_vkDestroyCudaFunctionNV( vkGetDeviceProcAddr( device, "vkDestroyCudaFunctionNV" ) );
        vkCmdCudaLaunchKernelNV = PFN_vkCmdCudaLaunchKernelNV( vkGetDeviceProcAddr( device, "vkCmdCudaLaunchKernelNV" ) );
#endif /*VK_ENABLE_BETA_EXTENSIONS*/

        //=== VK_QCOM_tile_shading ===
        vkCmdDispatchTileQCOM          = PFN_vkCmdDispatchTileQCOM( vkGetDeviceProcAddr( device, "vkCmdDispatchTileQCOM" ) );
        vkCmdBeginPerTileExecutionQCOM = PFN_vkCmdBeginPerTileExecutionQCOM( vkGetDeviceProcAddr( device, "vkCmdBeginPerTileExecutionQCOM" ) );
        vkCmdEndPerTileExecutionQCOM   = PFN_vkCmdEndPerTileExecutionQCOM( vkGetDeviceProcAddr( device, "vkCmdEndPerTileExecutionQCOM" ) );

#if defined( VK_USE_PLATFORM_METAL_EXT )
        //=== VK_EXT_metal_objects ===
        vkExportMetalObjectsEXT = PFN_vkExportMetalObjectsEXT( vkGetDeviceProcAddr( device, "vkExportMetalObjectsEXT" ) );
#endif /*VK_USE_PLATFORM_METAL_EXT*/

        //=== VK_KHR_synchronization2 ===
        vkCmdSetEvent2KHR = PFN_vkCmdSetEvent2KHR( vkGetDeviceProcAddr( device, "vkCmdSetEvent2KHR" ) );
        if ( !vkCmdSetEvent2 )
          vkCmdSetEvent2 = vkCmdSetEvent2KHR;
        vkCmdResetEvent2KHR = PFN_vkCmdResetEvent2KHR( vkGetDeviceProcAddr( device, "vkCmdResetEvent2KHR" ) );
        if ( !vkCmdResetEvent2 )
          vkCmdResetEvent2 = vkCmdResetEvent2KHR;
        vkCmdWaitEvents2KHR = PFN_vkCmdWaitEvents2KHR( vkGetDeviceProcAddr( device, "vkCmdWaitEvents2KHR" ) );
        if ( !vkCmdWaitEvents2 )
          vkCmdWaitEvents2 = vkCmdWaitEvents2KHR;
        vkCmdPipelineBarrier2KHR = PFN_vkCmdPipelineBarrier2KHR( vkGetDeviceProcAddr( device, "vkCmdPipelineBarrier2KHR" ) );
        if ( !vkCmdPipelineBarrier2 )
          vkCmdPipelineBarrier2 = vkCmdPipelineBarrier2KHR;
        vkCmdWriteTimestamp2KHR = PFN_vkCmdWriteTimestamp2KHR( vkGetDeviceProcAddr( device, "vkCmdWriteTimestamp2KHR" ) );
        if ( !vkCmdWriteTimestamp2 )
          vkCmdWriteTimestamp2 = vkCmdWriteTimestamp2KHR;
        vkQueueSubmit2KHR = PFN_vkQueueSubmit2KHR( vkGetDeviceProcAddr( device, "vkQueueSubmit2KHR" ) );
        if ( !vkQueueSubmit2 )
          vkQueueSubmit2 = vkQueueSubmit2KHR;

        //=== VK_EXT_descriptor_buffer ===
        vkGetDescriptorSetLayoutSizeEXT = PFN_vkGetDescriptorSetLayoutSizeEXT( vkGetDeviceProcAddr( device, "vkGetDescriptorSetLayoutSizeEXT" ) );
        vkGetDescriptorSetLayoutBindingOffsetEXT =
          PFN_vkGetDescriptorSetLayoutBindingOffsetEXT( vkGetDeviceProcAddr( device, "vkGetDescriptorSetLayoutBindingOffsetEXT" ) );
        vkGetDescriptorEXT                 = PFN_vkGetDescriptorEXT( vkGetDeviceProcAddr( device, "vkGetDescriptorEXT" ) );
        vkCmdBindDescriptorBuffersEXT      = PFN_vkCmdBindDescriptorBuffersEXT( vkGetDeviceProcAddr( device, "vkCmdBindDescriptorBuffersEXT" ) );
        vkCmdSetDescriptorBufferOffsetsEXT = PFN_vkCmdSetDescriptorBufferOffsetsEXT( vkGetDeviceProcAddr( device, "vkCmdSetDescriptorBufferOffsetsEXT" ) );
        vkCmdBindDescriptorBufferEmbeddedSamplersEXT =
          PFN_vkCmdBindDescriptorBufferEmbeddedSamplersEXT( vkGetDeviceProcAddr( device, "vkCmdBindDescriptorBufferEmbeddedSamplersEXT" ) );
        vkGetBufferOpaqueCaptureDescriptorDataEXT =
          PFN_vkGetBufferOpaqueCaptureDescriptorDataEXT( vkGetDeviceProcAddr( device, "vkGetBufferOpaqueCaptureDescriptorDataEXT" ) );
        vkGetImageOpaqueCaptureDescriptorDataEXT =
          PFN_vkGetImageOpaqueCaptureDescriptorDataEXT( vkGetDeviceProcAddr( device, "vkGetImageOpaqueCaptureDescriptorDataEXT" ) );
        vkGetImageViewOpaqueCaptureDescriptorDataEXT =
          PFN_vkGetImageViewOpaqueCaptureDescriptorDataEXT( vkGetDeviceProcAddr( device, "vkGetImageViewOpaqueCaptureDescriptorDataEXT" ) );
        vkGetSamplerOpaqueCaptureDescriptorDataEXT =
          PFN_vkGetSamplerOpaqueCaptureDescriptorDataEXT( vkGetDeviceProcAddr( device, "vkGetSamplerOpaqueCaptureDescriptorDataEXT" ) );
        vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT = PFN_vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT(
          vkGetDeviceProcAddr( device, "vkGetAccelerationStructureOpaqueCaptureDescriptorDataEXT" ) );

        //=== VK_KHR_device_address_commands ===
        vkCmdBindIndexBuffer3KHR     = PFN_vkCmdBindIndexBuffer3KHR( vkGetDeviceProcAddr( device, "vkCmdBindIndexBuffer3KHR" ) );
        vkCmdBindVertexBuffers3KHR   = PFN_vkCmdBindVertexBuffers3KHR( vkGetDeviceProcAddr( device, "vkCmdBindVertexBuffers3KHR" ) );
        vkCmdDrawIndirect2KHR        = PFN_vkCmdDrawIndirect2KHR( vkGetDeviceProcAddr( device, "vkCmdDrawIndirect2KHR" ) );
        vkCmdDrawIndexedIndirect2KHR = PFN_vkCmdDrawIndexedIndirect2KHR( vkGetDeviceProcAddr( device, "vkCmdDrawIndexedIndirect2KHR" ) );
        vkCmdDispatchIndirect2KHR    = PFN_vkCmdDispatchIndirect2KHR( vkGetDeviceProcAddr( device, "vkCmdDispatchIndirect2KHR" ) );
        vkCmdCopyMemoryKHR           = PFN_vkCmdCopyMemoryKHR( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryKHR" ) );
        vkCmdCopyMemoryToImageKHR    = PFN_vkCmdCopyMemoryToImageKHR( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryToImageKHR" ) );
        vkCmdCopyImageToMemoryKHR    = PFN_vkCmdCopyImageToMemoryKHR( vkGetDeviceProcAddr( device, "vkCmdCopyImageToMemoryKHR" ) );
        vkCmdUpdateMemoryKHR         = PFN_vkCmdUpdateMemoryKHR( vkGetDeviceProcAddr( device, "vkCmdUpdateMemoryKHR" ) );
        vkCmdFillMemoryKHR           = PFN_vkCmdFillMemoryKHR( vkGetDeviceProcAddr( device, "vkCmdFillMemoryKHR" ) );
        vkCmdCopyQueryPoolResultsToMemoryKHR =
          PFN_vkCmdCopyQueryPoolResultsToMemoryKHR( vkGetDeviceProcAddr( device, "vkCmdCopyQueryPoolResultsToMemoryKHR" ) );
        vkCmdDrawIndirectCount2KHR         = PFN_vkCmdDrawIndirectCount2KHR( vkGetDeviceProcAddr( device, "vkCmdDrawIndirectCount2KHR" ) );
        vkCmdDrawIndexedIndirectCount2KHR  = PFN_vkCmdDrawIndexedIndirectCount2KHR( vkGetDeviceProcAddr( device, "vkCmdDrawIndexedIndirectCount2KHR" ) );
        vkCmdBeginConditionalRendering2EXT = PFN_vkCmdBeginConditionalRendering2EXT( vkGetDeviceProcAddr( device, "vkCmdBeginConditionalRendering2EXT" ) );
        vkCmdBindTransformFeedbackBuffers2EXT =
          PFN_vkCmdBindTransformFeedbackBuffers2EXT( vkGetDeviceProcAddr( device, "vkCmdBindTransformFeedbackBuffers2EXT" ) );
        vkCmdBeginTransformFeedback2EXT     = PFN_vkCmdBeginTransformFeedback2EXT( vkGetDeviceProcAddr( device, "vkCmdBeginTransformFeedback2EXT" ) );
        vkCmdEndTransformFeedback2EXT       = PFN_vkCmdEndTransformFeedback2EXT( vkGetDeviceProcAddr( device, "vkCmdEndTransformFeedback2EXT" ) );
        vkCmdDrawIndirectByteCount2EXT      = PFN_vkCmdDrawIndirectByteCount2EXT( vkGetDeviceProcAddr( device, "vkCmdDrawIndirectByteCount2EXT" ) );
        vkCmdDrawMeshTasksIndirect2EXT      = PFN_vkCmdDrawMeshTasksIndirect2EXT( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksIndirect2EXT" ) );
        vkCmdDrawMeshTasksIndirectCount2EXT = PFN_vkCmdDrawMeshTasksIndirectCount2EXT( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksIndirectCount2EXT" ) );
        vkCmdWriteMarkerToMemoryAMD         = PFN_vkCmdWriteMarkerToMemoryAMD( vkGetDeviceProcAddr( device, "vkCmdWriteMarkerToMemoryAMD" ) );
        vkCreateAccelerationStructure2KHR   = PFN_vkCreateAccelerationStructure2KHR( vkGetDeviceProcAddr( device, "vkCreateAccelerationStructure2KHR" ) );

        //=== VK_NV_fragment_shading_rate_enums ===
        vkCmdSetFragmentShadingRateEnumNV = PFN_vkCmdSetFragmentShadingRateEnumNV( vkGetDeviceProcAddr( device, "vkCmdSetFragmentShadingRateEnumNV" ) );

        //=== VK_EXT_mesh_shader ===
        vkCmdDrawMeshTasksEXT              = PFN_vkCmdDrawMeshTasksEXT( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksEXT" ) );
        vkCmdDrawMeshTasksIndirectEXT      = PFN_vkCmdDrawMeshTasksIndirectEXT( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksIndirectEXT" ) );
        vkCmdDrawMeshTasksIndirectCountEXT = PFN_vkCmdDrawMeshTasksIndirectCountEXT( vkGetDeviceProcAddr( device, "vkCmdDrawMeshTasksIndirectCountEXT" ) );

        //=== VK_KHR_copy_commands2 ===
        vkCmdCopyBuffer2KHR = PFN_vkCmdCopyBuffer2KHR( vkGetDeviceProcAddr( device, "vkCmdCopyBuffer2KHR" ) );
        if ( !vkCmdCopyBuffer2 )
          vkCmdCopyBuffer2 = vkCmdCopyBuffer2KHR;
        vkCmdCopyImage2KHR = PFN_vkCmdCopyImage2KHR( vkGetDeviceProcAddr( device, "vkCmdCopyImage2KHR" ) );
        if ( !vkCmdCopyImage2 )
          vkCmdCopyImage2 = vkCmdCopyImage2KHR;
        vkCmdCopyBufferToImage2KHR = PFN_vkCmdCopyBufferToImage2KHR( vkGetDeviceProcAddr( device, "vkCmdCopyBufferToImage2KHR" ) );
        if ( !vkCmdCopyBufferToImage2 )
          vkCmdCopyBufferToImage2 = vkCmdCopyBufferToImage2KHR;
        vkCmdCopyImageToBuffer2KHR = PFN_vkCmdCopyImageToBuffer2KHR( vkGetDeviceProcAddr( device, "vkCmdCopyImageToBuffer2KHR" ) );
        if ( !vkCmdCopyImageToBuffer2 )
          vkCmdCopyImageToBuffer2 = vkCmdCopyImageToBuffer2KHR;
        vkCmdBlitImage2KHR = PFN_vkCmdBlitImage2KHR( vkGetDeviceProcAddr( device, "vkCmdBlitImage2KHR" ) );
        if ( !vkCmdBlitImage2 )
          vkCmdBlitImage2 = vkCmdBlitImage2KHR;
        vkCmdResolveImage2KHR = PFN_vkCmdResolveImage2KHR( vkGetDeviceProcAddr( device, "vkCmdResolveImage2KHR" ) );
        if ( !vkCmdResolveImage2 )
          vkCmdResolveImage2 = vkCmdResolveImage2KHR;

        //=== VK_EXT_device_fault ===
        vkGetDeviceFaultInfoEXT = PFN_vkGetDeviceFaultInfoEXT( vkGetDeviceProcAddr( device, "vkGetDeviceFaultInfoEXT" ) );

        //=== VK_EXT_vertex_input_dynamic_state ===
        vkCmdSetVertexInputEXT = PFN_vkCmdSetVertexInputEXT( vkGetDeviceProcAddr( device, "vkCmdSetVertexInputEXT" ) );

#if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_external_memory ===
        vkGetMemoryZirconHandleFUCHSIA = PFN_vkGetMemoryZirconHandleFUCHSIA( vkGetDeviceProcAddr( device, "vkGetMemoryZirconHandleFUCHSIA" ) );
        vkGetMemoryZirconHandlePropertiesFUCHSIA =
          PFN_vkGetMemoryZirconHandlePropertiesFUCHSIA( vkGetDeviceProcAddr( device, "vkGetMemoryZirconHandlePropertiesFUCHSIA" ) );
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_external_semaphore ===
        vkImportSemaphoreZirconHandleFUCHSIA =
          PFN_vkImportSemaphoreZirconHandleFUCHSIA( vkGetDeviceProcAddr( device, "vkImportSemaphoreZirconHandleFUCHSIA" ) );
        vkGetSemaphoreZirconHandleFUCHSIA = PFN_vkGetSemaphoreZirconHandleFUCHSIA( vkGetDeviceProcAddr( device, "vkGetSemaphoreZirconHandleFUCHSIA" ) );
#endif /*VK_USE_PLATFORM_FUCHSIA*/

#if defined( VK_USE_PLATFORM_FUCHSIA )
        //=== VK_FUCHSIA_buffer_collection ===
        vkCreateBufferCollectionFUCHSIA = PFN_vkCreateBufferCollectionFUCHSIA( vkGetDeviceProcAddr( device, "vkCreateBufferCollectionFUCHSIA" ) );
        vkSetBufferCollectionImageConstraintsFUCHSIA =
          PFN_vkSetBufferCollectionImageConstraintsFUCHSIA( vkGetDeviceProcAddr( device, "vkSetBufferCollectionImageConstraintsFUCHSIA" ) );
        vkSetBufferCollectionBufferConstraintsFUCHSIA =
          PFN_vkSetBufferCollectionBufferConstraintsFUCHSIA( vkGetDeviceProcAddr( device, "vkSetBufferCollectionBufferConstraintsFUCHSIA" ) );
        vkDestroyBufferCollectionFUCHSIA = PFN_vkDestroyBufferCollectionFUCHSIA( vkGetDeviceProcAddr( device, "vkDestroyBufferCollectionFUCHSIA" ) );
        vkGetBufferCollectionPropertiesFUCHSIA =
          PFN_vkGetBufferCollectionPropertiesFUCHSIA( vkGetDeviceProcAddr( device, "vkGetBufferCollectionPropertiesFUCHSIA" ) );
#endif /*VK_USE_PLATFORM_FUCHSIA*/

        //=== VK_HUAWEI_subpass_shading ===
        vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI =
          PFN_vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI( vkGetDeviceProcAddr( device, "vkGetDeviceSubpassShadingMaxWorkgroupSizeHUAWEI" ) );
        vkCmdSubpassShadingHUAWEI = PFN_vkCmdSubpassShadingHUAWEI( vkGetDeviceProcAddr( device, "vkCmdSubpassShadingHUAWEI" ) );

        //=== VK_HUAWEI_invocation_mask ===
        vkCmdBindInvocationMaskHUAWEI = PFN_vkCmdBindInvocationMaskHUAWEI( vkGetDeviceProcAddr( device, "vkCmdBindInvocationMaskHUAWEI" ) );

        //=== VK_NV_external_memory_rdma ===
        vkGetMemoryRemoteAddressNV = PFN_vkGetMemoryRemoteAddressNV( vkGetDeviceProcAddr( device, "vkGetMemoryRemoteAddressNV" ) );

        //=== VK_EXT_pipeline_properties ===
        vkGetPipelinePropertiesEXT = PFN_vkGetPipelinePropertiesEXT( vkGetDeviceProcAddr( device, "vkGetPipelinePropertiesEXT" ) );

        //=== VK_EXT_extended_dynamic_state2 ===
        vkCmdSetPatchControlPointsEXT      = PFN_vkCmdSetPatchControlPointsEXT( vkGetDeviceProcAddr( device, "vkCmdSetPatchControlPointsEXT" ) );
        vkCmdSetRasterizerDiscardEnableEXT = PFN_vkCmdSetRasterizerDiscardEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetRasterizerDiscardEnableEXT" ) );
        if ( !vkCmdSetRasterizerDiscardEnable )
          vkCmdSetRasterizerDiscardEnable = vkCmdSetRasterizerDiscardEnableEXT;
        vkCmdSetDepthBiasEnableEXT = PFN_vkCmdSetDepthBiasEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthBiasEnableEXT" ) );
        if ( !vkCmdSetDepthBiasEnable )
          vkCmdSetDepthBiasEnable = vkCmdSetDepthBiasEnableEXT;
        vkCmdSetLogicOpEXT                = PFN_vkCmdSetLogicOpEXT( vkGetDeviceProcAddr( device, "vkCmdSetLogicOpEXT" ) );
        vkCmdSetPrimitiveRestartEnableEXT = PFN_vkCmdSetPrimitiveRestartEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetPrimitiveRestartEnableEXT" ) );
        if ( !vkCmdSetPrimitiveRestartEnable )
          vkCmdSetPrimitiveRestartEnable = vkCmdSetPrimitiveRestartEnableEXT;

        //=== VK_EXT_color_write_enable ===
        vkCmdSetColorWriteEnableEXT = PFN_vkCmdSetColorWriteEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetColorWriteEnableEXT" ) );

        //=== VK_KHR_ray_tracing_maintenance1 ===
        vkCmdTraceRaysIndirect2KHR = PFN_vkCmdTraceRaysIndirect2KHR( vkGetDeviceProcAddr( device, "vkCmdTraceRaysIndirect2KHR" ) );

        //=== VK_EXT_multi_draw ===
        vkCmdDrawMultiEXT        = PFN_vkCmdDrawMultiEXT( vkGetDeviceProcAddr( device, "vkCmdDrawMultiEXT" ) );
        vkCmdDrawMultiIndexedEXT = PFN_vkCmdDrawMultiIndexedEXT( vkGetDeviceProcAddr( device, "vkCmdDrawMultiIndexedEXT" ) );

        //=== VK_EXT_opacity_micromap ===
        vkCreateMicromapEXT                 = PFN_vkCreateMicromapEXT( vkGetDeviceProcAddr( device, "vkCreateMicromapEXT" ) );
        vkDestroyMicromapEXT                = PFN_vkDestroyMicromapEXT( vkGetDeviceProcAddr( device, "vkDestroyMicromapEXT" ) );
        vkCmdBuildMicromapsEXT              = PFN_vkCmdBuildMicromapsEXT( vkGetDeviceProcAddr( device, "vkCmdBuildMicromapsEXT" ) );
        vkBuildMicromapsEXT                 = PFN_vkBuildMicromapsEXT( vkGetDeviceProcAddr( device, "vkBuildMicromapsEXT" ) );
        vkCopyMicromapEXT                   = PFN_vkCopyMicromapEXT( vkGetDeviceProcAddr( device, "vkCopyMicromapEXT" ) );
        vkCopyMicromapToMemoryEXT           = PFN_vkCopyMicromapToMemoryEXT( vkGetDeviceProcAddr( device, "vkCopyMicromapToMemoryEXT" ) );
        vkCopyMemoryToMicromapEXT           = PFN_vkCopyMemoryToMicromapEXT( vkGetDeviceProcAddr( device, "vkCopyMemoryToMicromapEXT" ) );
        vkWriteMicromapsPropertiesEXT       = PFN_vkWriteMicromapsPropertiesEXT( vkGetDeviceProcAddr( device, "vkWriteMicromapsPropertiesEXT" ) );
        vkCmdCopyMicromapEXT                = PFN_vkCmdCopyMicromapEXT( vkGetDeviceProcAddr( device, "vkCmdCopyMicromapEXT" ) );
        vkCmdCopyMicromapToMemoryEXT        = PFN_vkCmdCopyMicromapToMemoryEXT( vkGetDeviceProcAddr( device, "vkCmdCopyMicromapToMemoryEXT" ) );
        vkCmdCopyMemoryToMicromapEXT        = PFN_vkCmdCopyMemoryToMicromapEXT( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryToMicromapEXT" ) );
        vkCmdWriteMicromapsPropertiesEXT    = PFN_vkCmdWriteMicromapsPropertiesEXT( vkGetDeviceProcAddr( device, "vkCmdWriteMicromapsPropertiesEXT" ) );
        vkGetDeviceMicromapCompatibilityEXT = PFN_vkGetDeviceMicromapCompatibilityEXT( vkGetDeviceProcAddr( device, "vkGetDeviceMicromapCompatibilityEXT" ) );
        vkGetMicromapBuildSizesEXT          = PFN_vkGetMicromapBuildSizesEXT( vkGetDeviceProcAddr( device, "vkGetMicromapBuildSizesEXT" ) );

        //=== VK_HUAWEI_cluster_culling_shader ===
        vkCmdDrawClusterHUAWEI         = PFN_vkCmdDrawClusterHUAWEI( vkGetDeviceProcAddr( device, "vkCmdDrawClusterHUAWEI" ) );
        vkCmdDrawClusterIndirectHUAWEI = PFN_vkCmdDrawClusterIndirectHUAWEI( vkGetDeviceProcAddr( device, "vkCmdDrawClusterIndirectHUAWEI" ) );

        //=== VK_EXT_pageable_device_local_memory ===
        vkSetDeviceMemoryPriorityEXT = PFN_vkSetDeviceMemoryPriorityEXT( vkGetDeviceProcAddr( device, "vkSetDeviceMemoryPriorityEXT" ) );

        //=== VK_KHR_maintenance4 ===
        vkGetDeviceBufferMemoryRequirementsKHR =
          PFN_vkGetDeviceBufferMemoryRequirementsKHR( vkGetDeviceProcAddr( device, "vkGetDeviceBufferMemoryRequirementsKHR" ) );
        if ( !vkGetDeviceBufferMemoryRequirements )
          vkGetDeviceBufferMemoryRequirements = vkGetDeviceBufferMemoryRequirementsKHR;
        vkGetDeviceImageMemoryRequirementsKHR =
          PFN_vkGetDeviceImageMemoryRequirementsKHR( vkGetDeviceProcAddr( device, "vkGetDeviceImageMemoryRequirementsKHR" ) );
        if ( !vkGetDeviceImageMemoryRequirements )
          vkGetDeviceImageMemoryRequirements = vkGetDeviceImageMemoryRequirementsKHR;
        vkGetDeviceImageSparseMemoryRequirementsKHR =
          PFN_vkGetDeviceImageSparseMemoryRequirementsKHR( vkGetDeviceProcAddr( device, "vkGetDeviceImageSparseMemoryRequirementsKHR" ) );
        if ( !vkGetDeviceImageSparseMemoryRequirements )
          vkGetDeviceImageSparseMemoryRequirements = vkGetDeviceImageSparseMemoryRequirementsKHR;

        //=== VK_ARM_scheduling_controls ===
        vkCmdSetDispatchParametersARM = PFN_vkCmdSetDispatchParametersARM( vkGetDeviceProcAddr( device, "vkCmdSetDispatchParametersARM" ) );

        //=== VK_VALVE_descriptor_set_host_mapping ===
        vkGetDescriptorSetLayoutHostMappingInfoVALVE =
          PFN_vkGetDescriptorSetLayoutHostMappingInfoVALVE( vkGetDeviceProcAddr( device, "vkGetDescriptorSetLayoutHostMappingInfoVALVE" ) );
        vkGetDescriptorSetHostMappingVALVE = PFN_vkGetDescriptorSetHostMappingVALVE( vkGetDeviceProcAddr( device, "vkGetDescriptorSetHostMappingVALVE" ) );

        //=== VK_NV_copy_memory_indirect ===
        vkCmdCopyMemoryIndirectNV        = PFN_vkCmdCopyMemoryIndirectNV( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryIndirectNV" ) );
        vkCmdCopyMemoryToImageIndirectNV = PFN_vkCmdCopyMemoryToImageIndirectNV( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryToImageIndirectNV" ) );

        //=== VK_NV_memory_decompression ===
        vkCmdDecompressMemoryNV = PFN_vkCmdDecompressMemoryNV( vkGetDeviceProcAddr( device, "vkCmdDecompressMemoryNV" ) );
        vkCmdDecompressMemoryIndirectCountNV =
          PFN_vkCmdDecompressMemoryIndirectCountNV( vkGetDeviceProcAddr( device, "vkCmdDecompressMemoryIndirectCountNV" ) );

        //=== VK_NV_device_generated_commands_compute ===
        vkGetPipelineIndirectMemoryRequirementsNV =
          PFN_vkGetPipelineIndirectMemoryRequirementsNV( vkGetDeviceProcAddr( device, "vkGetPipelineIndirectMemoryRequirementsNV" ) );
        vkCmdUpdatePipelineIndirectBufferNV = PFN_vkCmdUpdatePipelineIndirectBufferNV( vkGetDeviceProcAddr( device, "vkCmdUpdatePipelineIndirectBufferNV" ) );
        vkGetPipelineIndirectDeviceAddressNV =
          PFN_vkGetPipelineIndirectDeviceAddressNV( vkGetDeviceProcAddr( device, "vkGetPipelineIndirectDeviceAddressNV" ) );

#if defined( VK_USE_PLATFORM_OHOS )
        //=== VK_OHOS_external_memory ===
        vkGetNativeBufferPropertiesOHOS = PFN_vkGetNativeBufferPropertiesOHOS( vkGetDeviceProcAddr( device, "vkGetNativeBufferPropertiesOHOS" ) );
        vkGetMemoryNativeBufferOHOS     = PFN_vkGetMemoryNativeBufferOHOS( vkGetDeviceProcAddr( device, "vkGetMemoryNativeBufferOHOS" ) );
#endif /*VK_USE_PLATFORM_OHOS*/

        //=== VK_EXT_extended_dynamic_state3 ===
        vkCmdSetDepthClampEnableEXT         = PFN_vkCmdSetDepthClampEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthClampEnableEXT" ) );
        vkCmdSetPolygonModeEXT              = PFN_vkCmdSetPolygonModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetPolygonModeEXT" ) );
        vkCmdSetRasterizationSamplesEXT     = PFN_vkCmdSetRasterizationSamplesEXT( vkGetDeviceProcAddr( device, "vkCmdSetRasterizationSamplesEXT" ) );
        vkCmdSetSampleMaskEXT               = PFN_vkCmdSetSampleMaskEXT( vkGetDeviceProcAddr( device, "vkCmdSetSampleMaskEXT" ) );
        vkCmdSetAlphaToCoverageEnableEXT    = PFN_vkCmdSetAlphaToCoverageEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetAlphaToCoverageEnableEXT" ) );
        vkCmdSetAlphaToOneEnableEXT         = PFN_vkCmdSetAlphaToOneEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetAlphaToOneEnableEXT" ) );
        vkCmdSetLogicOpEnableEXT            = PFN_vkCmdSetLogicOpEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetLogicOpEnableEXT" ) );
        vkCmdSetColorBlendEnableEXT         = PFN_vkCmdSetColorBlendEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetColorBlendEnableEXT" ) );
        vkCmdSetColorBlendEquationEXT       = PFN_vkCmdSetColorBlendEquationEXT( vkGetDeviceProcAddr( device, "vkCmdSetColorBlendEquationEXT" ) );
        vkCmdSetColorWriteMaskEXT           = PFN_vkCmdSetColorWriteMaskEXT( vkGetDeviceProcAddr( device, "vkCmdSetColorWriteMaskEXT" ) );
        vkCmdSetTessellationDomainOriginEXT = PFN_vkCmdSetTessellationDomainOriginEXT( vkGetDeviceProcAddr( device, "vkCmdSetTessellationDomainOriginEXT" ) );
        vkCmdSetRasterizationStreamEXT      = PFN_vkCmdSetRasterizationStreamEXT( vkGetDeviceProcAddr( device, "vkCmdSetRasterizationStreamEXT" ) );
        vkCmdSetConservativeRasterizationModeEXT =
          PFN_vkCmdSetConservativeRasterizationModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetConservativeRasterizationModeEXT" ) );
        vkCmdSetExtraPrimitiveOverestimationSizeEXT =
          PFN_vkCmdSetExtraPrimitiveOverestimationSizeEXT( vkGetDeviceProcAddr( device, "vkCmdSetExtraPrimitiveOverestimationSizeEXT" ) );
        vkCmdSetDepthClipEnableEXT       = PFN_vkCmdSetDepthClipEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthClipEnableEXT" ) );
        vkCmdSetSampleLocationsEnableEXT = PFN_vkCmdSetSampleLocationsEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetSampleLocationsEnableEXT" ) );
        vkCmdSetColorBlendAdvancedEXT    = PFN_vkCmdSetColorBlendAdvancedEXT( vkGetDeviceProcAddr( device, "vkCmdSetColorBlendAdvancedEXT" ) );
        vkCmdSetProvokingVertexModeEXT   = PFN_vkCmdSetProvokingVertexModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetProvokingVertexModeEXT" ) );
        vkCmdSetLineRasterizationModeEXT = PFN_vkCmdSetLineRasterizationModeEXT( vkGetDeviceProcAddr( device, "vkCmdSetLineRasterizationModeEXT" ) );
        vkCmdSetLineStippleEnableEXT     = PFN_vkCmdSetLineStippleEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetLineStippleEnableEXT" ) );
        vkCmdSetDepthClipNegativeOneToOneEXT =
          PFN_vkCmdSetDepthClipNegativeOneToOneEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthClipNegativeOneToOneEXT" ) );
        vkCmdSetViewportWScalingEnableNV  = PFN_vkCmdSetViewportWScalingEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetViewportWScalingEnableNV" ) );
        vkCmdSetViewportSwizzleNV         = PFN_vkCmdSetViewportSwizzleNV( vkGetDeviceProcAddr( device, "vkCmdSetViewportSwizzleNV" ) );
        vkCmdSetCoverageToColorEnableNV   = PFN_vkCmdSetCoverageToColorEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageToColorEnableNV" ) );
        vkCmdSetCoverageToColorLocationNV = PFN_vkCmdSetCoverageToColorLocationNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageToColorLocationNV" ) );
        vkCmdSetCoverageModulationModeNV  = PFN_vkCmdSetCoverageModulationModeNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageModulationModeNV" ) );
        vkCmdSetCoverageModulationTableEnableNV =
          PFN_vkCmdSetCoverageModulationTableEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageModulationTableEnableNV" ) );
        vkCmdSetCoverageModulationTableNV = PFN_vkCmdSetCoverageModulationTableNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageModulationTableNV" ) );
        vkCmdSetShadingRateImageEnableNV  = PFN_vkCmdSetShadingRateImageEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetShadingRateImageEnableNV" ) );
        vkCmdSetRepresentativeFragmentTestEnableNV =
          PFN_vkCmdSetRepresentativeFragmentTestEnableNV( vkGetDeviceProcAddr( device, "vkCmdSetRepresentativeFragmentTestEnableNV" ) );
        vkCmdSetCoverageReductionModeNV = PFN_vkCmdSetCoverageReductionModeNV( vkGetDeviceProcAddr( device, "vkCmdSetCoverageReductionModeNV" ) );

        //=== VK_ARM_tensors ===
        vkCreateTensorARM                = PFN_vkCreateTensorARM( vkGetDeviceProcAddr( device, "vkCreateTensorARM" ) );
        vkDestroyTensorARM               = PFN_vkDestroyTensorARM( vkGetDeviceProcAddr( device, "vkDestroyTensorARM" ) );
        vkCreateTensorViewARM            = PFN_vkCreateTensorViewARM( vkGetDeviceProcAddr( device, "vkCreateTensorViewARM" ) );
        vkDestroyTensorViewARM           = PFN_vkDestroyTensorViewARM( vkGetDeviceProcAddr( device, "vkDestroyTensorViewARM" ) );
        vkGetTensorMemoryRequirementsARM = PFN_vkGetTensorMemoryRequirementsARM( vkGetDeviceProcAddr( device, "vkGetTensorMemoryRequirementsARM" ) );
        vkBindTensorMemoryARM            = PFN_vkBindTensorMemoryARM( vkGetDeviceProcAddr( device, "vkBindTensorMemoryARM" ) );
        vkGetDeviceTensorMemoryRequirementsARM =
          PFN_vkGetDeviceTensorMemoryRequirementsARM( vkGetDeviceProcAddr( device, "vkGetDeviceTensorMemoryRequirementsARM" ) );
        vkCmdCopyTensorARM = PFN_vkCmdCopyTensorARM( vkGetDeviceProcAddr( device, "vkCmdCopyTensorARM" ) );
        vkGetTensorOpaqueCaptureDescriptorDataARM =
          PFN_vkGetTensorOpaqueCaptureDescriptorDataARM( vkGetDeviceProcAddr( device, "vkGetTensorOpaqueCaptureDescriptorDataARM" ) );
        vkGetTensorViewOpaqueCaptureDescriptorDataARM =
          PFN_vkGetTensorViewOpaqueCaptureDescriptorDataARM( vkGetDeviceProcAddr( device, "vkGetTensorViewOpaqueCaptureDescriptorDataARM" ) );

        //=== VK_EXT_shader_module_identifier ===
        vkGetShaderModuleIdentifierEXT = PFN_vkGetShaderModuleIdentifierEXT( vkGetDeviceProcAddr( device, "vkGetShaderModuleIdentifierEXT" ) );
        vkGetShaderModuleCreateInfoIdentifierEXT =
          PFN_vkGetShaderModuleCreateInfoIdentifierEXT( vkGetDeviceProcAddr( device, "vkGetShaderModuleCreateInfoIdentifierEXT" ) );

        //=== VK_NV_optical_flow ===
        vkCreateOpticalFlowSessionNV    = PFN_vkCreateOpticalFlowSessionNV( vkGetDeviceProcAddr( device, "vkCreateOpticalFlowSessionNV" ) );
        vkDestroyOpticalFlowSessionNV   = PFN_vkDestroyOpticalFlowSessionNV( vkGetDeviceProcAddr( device, "vkDestroyOpticalFlowSessionNV" ) );
        vkBindOpticalFlowSessionImageNV = PFN_vkBindOpticalFlowSessionImageNV( vkGetDeviceProcAddr( device, "vkBindOpticalFlowSessionImageNV" ) );
        vkCmdOpticalFlowExecuteNV       = PFN_vkCmdOpticalFlowExecuteNV( vkGetDeviceProcAddr( device, "vkCmdOpticalFlowExecuteNV" ) );

        //=== VK_KHR_maintenance5 ===
        vkCmdBindIndexBuffer2KHR = PFN_vkCmdBindIndexBuffer2KHR( vkGetDeviceProcAddr( device, "vkCmdBindIndexBuffer2KHR" ) );
        if ( !vkCmdBindIndexBuffer2 )
          vkCmdBindIndexBuffer2 = vkCmdBindIndexBuffer2KHR;
        vkGetRenderingAreaGranularityKHR = PFN_vkGetRenderingAreaGranularityKHR( vkGetDeviceProcAddr( device, "vkGetRenderingAreaGranularityKHR" ) );
        if ( !vkGetRenderingAreaGranularity )
          vkGetRenderingAreaGranularity = vkGetRenderingAreaGranularityKHR;
        vkGetDeviceImageSubresourceLayoutKHR =
          PFN_vkGetDeviceImageSubresourceLayoutKHR( vkGetDeviceProcAddr( device, "vkGetDeviceImageSubresourceLayoutKHR" ) );
        if ( !vkGetDeviceImageSubresourceLayout )
          vkGetDeviceImageSubresourceLayout = vkGetDeviceImageSubresourceLayoutKHR;
        vkGetImageSubresourceLayout2KHR = PFN_vkGetImageSubresourceLayout2KHR( vkGetDeviceProcAddr( device, "vkGetImageSubresourceLayout2KHR" ) );
        if ( !vkGetImageSubresourceLayout2 )
          vkGetImageSubresourceLayout2 = vkGetImageSubresourceLayout2KHR;

        //=== VK_AMD_anti_lag ===
        vkAntiLagUpdateAMD = PFN_vkAntiLagUpdateAMD( vkGetDeviceProcAddr( device, "vkAntiLagUpdateAMD" ) );

        //=== VK_KHR_present_wait2 ===
        vkWaitForPresent2KHR = PFN_vkWaitForPresent2KHR( vkGetDeviceProcAddr( device, "vkWaitForPresent2KHR" ) );

        //=== VK_EXT_shader_object ===
        vkCreateShadersEXT         = PFN_vkCreateShadersEXT( vkGetDeviceProcAddr( device, "vkCreateShadersEXT" ) );
        vkDestroyShaderEXT         = PFN_vkDestroyShaderEXT( vkGetDeviceProcAddr( device, "vkDestroyShaderEXT" ) );
        vkGetShaderBinaryDataEXT   = PFN_vkGetShaderBinaryDataEXT( vkGetDeviceProcAddr( device, "vkGetShaderBinaryDataEXT" ) );
        vkCmdBindShadersEXT        = PFN_vkCmdBindShadersEXT( vkGetDeviceProcAddr( device, "vkCmdBindShadersEXT" ) );
        vkCmdSetDepthClampRangeEXT = PFN_vkCmdSetDepthClampRangeEXT( vkGetDeviceProcAddr( device, "vkCmdSetDepthClampRangeEXT" ) );

        //=== VK_KHR_pipeline_binary ===
        vkCreatePipelineBinariesKHR      = PFN_vkCreatePipelineBinariesKHR( vkGetDeviceProcAddr( device, "vkCreatePipelineBinariesKHR" ) );
        vkDestroyPipelineBinaryKHR       = PFN_vkDestroyPipelineBinaryKHR( vkGetDeviceProcAddr( device, "vkDestroyPipelineBinaryKHR" ) );
        vkGetPipelineKeyKHR              = PFN_vkGetPipelineKeyKHR( vkGetDeviceProcAddr( device, "vkGetPipelineKeyKHR" ) );
        vkGetPipelineBinaryDataKHR       = PFN_vkGetPipelineBinaryDataKHR( vkGetDeviceProcAddr( device, "vkGetPipelineBinaryDataKHR" ) );
        vkReleaseCapturedPipelineDataKHR = PFN_vkReleaseCapturedPipelineDataKHR( vkGetDeviceProcAddr( device, "vkReleaseCapturedPipelineDataKHR" ) );

        //=== VK_QCOM_tile_properties ===
        vkGetFramebufferTilePropertiesQCOM = PFN_vkGetFramebufferTilePropertiesQCOM( vkGetDeviceProcAddr( device, "vkGetFramebufferTilePropertiesQCOM" ) );
        vkGetDynamicRenderingTilePropertiesQCOM =
          PFN_vkGetDynamicRenderingTilePropertiesQCOM( vkGetDeviceProcAddr( device, "vkGetDynamicRenderingTilePropertiesQCOM" ) );

        //=== VK_KHR_swapchain_maintenance1 ===
        vkReleaseSwapchainImagesKHR = PFN_vkReleaseSwapchainImagesKHR( vkGetDeviceProcAddr( device, "vkReleaseSwapchainImagesKHR" ) );

        //=== VK_NV_cooperative_vector ===
        vkConvertCooperativeVectorMatrixNV = PFN_vkConvertCooperativeVectorMatrixNV( vkGetDeviceProcAddr( device, "vkConvertCooperativeVectorMatrixNV" ) );
        vkCmdConvertCooperativeVectorMatrixNV =
          PFN_vkCmdConvertCooperativeVectorMatrixNV( vkGetDeviceProcAddr( device, "vkCmdConvertCooperativeVectorMatrixNV" ) );

        //=== VK_NV_low_latency2 ===
        vkSetLatencySleepModeNV  = PFN_vkSetLatencySleepModeNV( vkGetDeviceProcAddr( device, "vkSetLatencySleepModeNV" ) );
        vkLatencySleepNV         = PFN_vkLatencySleepNV( vkGetDeviceProcAddr( device, "vkLatencySleepNV" ) );
        vkSetLatencyMarkerNV     = PFN_vkSetLatencyMarkerNV( vkGetDeviceProcAddr( device, "vkSetLatencyMarkerNV" ) );
        vkGetLatencyTimingsNV    = PFN_vkGetLatencyTimingsNV( vkGetDeviceProcAddr( device, "vkGetLatencyTimingsNV" ) );
        vkQueueNotifyOutOfBandNV = PFN_vkQueueNotifyOutOfBandNV( vkGetDeviceProcAddr( device, "vkQueueNotifyOutOfBandNV" ) );

        //=== VK_ARM_data_graph ===
        vkCreateDataGraphPipelinesARM       = PFN_vkCreateDataGraphPipelinesARM( vkGetDeviceProcAddr( device, "vkCreateDataGraphPipelinesARM" ) );
        vkCreateDataGraphPipelineSessionARM = PFN_vkCreateDataGraphPipelineSessionARM( vkGetDeviceProcAddr( device, "vkCreateDataGraphPipelineSessionARM" ) );
        vkGetDataGraphPipelineSessionBindPointRequirementsARM =
          PFN_vkGetDataGraphPipelineSessionBindPointRequirementsARM( vkGetDeviceProcAddr( device, "vkGetDataGraphPipelineSessionBindPointRequirementsARM" ) );
        vkGetDataGraphPipelineSessionMemoryRequirementsARM =
          PFN_vkGetDataGraphPipelineSessionMemoryRequirementsARM( vkGetDeviceProcAddr( device, "vkGetDataGraphPipelineSessionMemoryRequirementsARM" ) );
        vkBindDataGraphPipelineSessionMemoryARM =
          PFN_vkBindDataGraphPipelineSessionMemoryARM( vkGetDeviceProcAddr( device, "vkBindDataGraphPipelineSessionMemoryARM" ) );
        vkDestroyDataGraphPipelineSessionARM =
          PFN_vkDestroyDataGraphPipelineSessionARM( vkGetDeviceProcAddr( device, "vkDestroyDataGraphPipelineSessionARM" ) );
        vkCmdDispatchDataGraphARM = PFN_vkCmdDispatchDataGraphARM( vkGetDeviceProcAddr( device, "vkCmdDispatchDataGraphARM" ) );
        vkGetDataGraphPipelineAvailablePropertiesARM =
          PFN_vkGetDataGraphPipelineAvailablePropertiesARM( vkGetDeviceProcAddr( device, "vkGetDataGraphPipelineAvailablePropertiesARM" ) );
        vkGetDataGraphPipelinePropertiesARM = PFN_vkGetDataGraphPipelinePropertiesARM( vkGetDeviceProcAddr( device, "vkGetDataGraphPipelinePropertiesARM" ) );

        //=== VK_EXT_attachment_feedback_loop_dynamic_state ===
        vkCmdSetAttachmentFeedbackLoopEnableEXT =
          PFN_vkCmdSetAttachmentFeedbackLoopEnableEXT( vkGetDeviceProcAddr( device, "vkCmdSetAttachmentFeedbackLoopEnableEXT" ) );

#if defined( VK_USE_PLATFORM_SCREEN_QNX )
        //=== VK_QNX_external_memory_screen_buffer ===
        vkGetScreenBufferPropertiesQNX = PFN_vkGetScreenBufferPropertiesQNX( vkGetDeviceProcAddr( device, "vkGetScreenBufferPropertiesQNX" ) );
#endif /*VK_USE_PLATFORM_SCREEN_QNX*/

        //=== VK_KHR_line_rasterization ===
        vkCmdSetLineStippleKHR = PFN_vkCmdSetLineStippleKHR( vkGetDeviceProcAddr( device, "vkCmdSetLineStippleKHR" ) );
        if ( !vkCmdSetLineStipple )
          vkCmdSetLineStipple = vkCmdSetLineStippleKHR;

        //=== VK_KHR_calibrated_timestamps ===
        vkGetCalibratedTimestampsKHR = PFN_vkGetCalibratedTimestampsKHR( vkGetDeviceProcAddr( device, "vkGetCalibratedTimestampsKHR" ) );

        //=== VK_KHR_maintenance6 ===
        vkCmdBindDescriptorSets2KHR = PFN_vkCmdBindDescriptorSets2KHR( vkGetDeviceProcAddr( device, "vkCmdBindDescriptorSets2KHR" ) );
        if ( !vkCmdBindDescriptorSets2 )
          vkCmdBindDescriptorSets2 = vkCmdBindDescriptorSets2KHR;
        vkCmdPushConstants2KHR = PFN_vkCmdPushConstants2KHR( vkGetDeviceProcAddr( device, "vkCmdPushConstants2KHR" ) );
        if ( !vkCmdPushConstants2 )
          vkCmdPushConstants2 = vkCmdPushConstants2KHR;
        vkCmdPushDescriptorSet2KHR = PFN_vkCmdPushDescriptorSet2KHR( vkGetDeviceProcAddr( device, "vkCmdPushDescriptorSet2KHR" ) );
        if ( !vkCmdPushDescriptorSet2 )
          vkCmdPushDescriptorSet2 = vkCmdPushDescriptorSet2KHR;
        vkCmdPushDescriptorSetWithTemplate2KHR =
          PFN_vkCmdPushDescriptorSetWithTemplate2KHR( vkGetDeviceProcAddr( device, "vkCmdPushDescriptorSetWithTemplate2KHR" ) );
        if ( !vkCmdPushDescriptorSetWithTemplate2 )
          vkCmdPushDescriptorSetWithTemplate2 = vkCmdPushDescriptorSetWithTemplate2KHR;
        vkCmdSetDescriptorBufferOffsets2EXT = PFN_vkCmdSetDescriptorBufferOffsets2EXT( vkGetDeviceProcAddr( device, "vkCmdSetDescriptorBufferOffsets2EXT" ) );
        vkCmdBindDescriptorBufferEmbeddedSamplers2EXT =
          PFN_vkCmdBindDescriptorBufferEmbeddedSamplers2EXT( vkGetDeviceProcAddr( device, "vkCmdBindDescriptorBufferEmbeddedSamplers2EXT" ) );

        //=== VK_QCOM_tile_memory_heap ===
        vkCmdBindTileMemoryQCOM = PFN_vkCmdBindTileMemoryQCOM( vkGetDeviceProcAddr( device, "vkCmdBindTileMemoryQCOM" ) );

        //=== VK_KHR_copy_memory_indirect ===
        vkCmdCopyMemoryIndirectKHR        = PFN_vkCmdCopyMemoryIndirectKHR( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryIndirectKHR" ) );
        vkCmdCopyMemoryToImageIndirectKHR = PFN_vkCmdCopyMemoryToImageIndirectKHR( vkGetDeviceProcAddr( device, "vkCmdCopyMemoryToImageIndirectKHR" ) );

        //=== VK_EXT_memory_decompression ===
        vkCmdDecompressMemoryEXT = PFN_vkCmdDecompressMemoryEXT( vkGetDeviceProcAddr( device, "vkCmdDecompressMemoryEXT" ) );
        vkCmdDecompressMemoryIndirectCountEXT =
          PFN_vkCmdDecompressMemoryIndirectCountEXT( vkGetDeviceProcAddr( device, "vkCmdDecompressMemoryIndirectCountEXT" ) );

        //=== VK_NV_external_compute_queue ===
        vkCreateExternalComputeQueueNV  = PFN_vkCreateExternalComputeQueueNV( vkGetDeviceProcAddr( device, "vkCreateExternalComputeQueueNV" ) );
        vkDestroyExternalComputeQueueNV = PFN_vkDestroyExternalComputeQueueNV( vkGetDeviceProcAddr( device, "vkDestroyExternalComputeQueueNV" ) );
        vkGetExternalComputeQueueDataNV = PFN_vkGetExternalComputeQueueDataNV( vkGetDeviceProcAddr( device, "vkGetExternalComputeQueueDataNV" ) );

        //=== VK_NV_cluster_acceleration_structure ===
        vkGetClusterAccelerationStructureBuildSizesNV =
          PFN_vkGetClusterAccelerationStructureBuildSizesNV( vkGetDeviceProcAddr( device, "vkGetClusterAccelerationStructureBuildSizesNV" ) );
        vkCmdBuildClusterAccelerationStructureIndirectNV =
          PFN_vkCmdBuildClusterAccelerationStructureIndirectNV( vkGetDeviceProcAddr( device, "vkCmdBuildClusterAccelerationStructureIndirectNV" ) );

        //=== VK_NV_partitioned_acceleration_structure ===
        vkGetPartitionedAccelerationStructuresBuildSizesNV =
          PFN_vkGetPartitionedAccelerationStructuresBuildSizesNV( vkGetDeviceProcAddr( device, "vkGetPartitionedAccelerationStructuresBuildSizesNV" ) );
        vkCmdBuildPartitionedAccelerationStructuresNV =
          PFN_vkCmdBuildPartitionedAccelerationStructuresNV( vkGetDeviceProcAddr( device, "vkCmdBuildPartitionedAccelerationStructuresNV" ) );

        //=== VK_EXT_device_generated_commands ===
        vkGetGeneratedCommandsMemoryRequirementsEXT =
          PFN_vkGetGeneratedCommandsMemoryRequirementsEXT( vkGetDeviceProcAddr( device, "vkGetGeneratedCommandsMemoryRequirementsEXT" ) );
        vkCmdPreprocessGeneratedCommandsEXT = PFN_vkCmdPreprocessGeneratedCommandsEXT( vkGetDeviceProcAddr( device, "vkCmdPreprocessGeneratedCommandsEXT" ) );
        vkCmdExecuteGeneratedCommandsEXT    = PFN_vkCmdExecuteGeneratedCommandsEXT( vkGetDeviceProcAddr( device, "vkCmdExecuteGeneratedCommandsEXT" ) );
        vkCreateIndirectCommandsLayoutEXT   = PFN_vkCreateIndirectCommandsLayoutEXT( vkGetDeviceProcAddr( device, "vkCreateIndirectCommandsLayoutEXT" ) );
        vkDestroyIndirectCommandsLayoutEXT  = PFN_vkDestroyIndirectCommandsLayoutEXT( vkGetDeviceProcAddr( device, "vkDestroyIndirectCommandsLayoutEXT" ) );
        vkCreateIndirectExecutionSetEXT     = PFN_vkCreateIndirectExecutionSetEXT( vkGetDeviceProcAddr( device, "vkCreateIndirectExecutionSetEXT" ) );
        vkDestroyIndirectExecutionSetEXT    = PFN_vkDestroyIndirectExecutionSetEXT( vkGetDeviceProcAddr( device, "vkDestroyIndirectExecutionSetEXT" ) );
        vkUpdateIndirectExecutionSetPipelineEXT =
          PFN_vkUpdateIndirectExecutionSetPipelineEXT( vkGetDeviceProcAddr( device, "vkUpdateIndirectExecutionSetPipelineEXT" ) );
        vkUpdateIndirectExecutionSetShaderEXT =
          PFN_vkUpdateIndirectExecutionSetShaderEXT( vkGetDeviceProcAddr( device, "vkUpdateIndirectExecutionSetShaderEXT" ) );

        //=== VK_KHR_device_fault ===
        vkGetDeviceFaultReportsKHR   = PFN_vkGetDeviceFaultReportsKHR( vkGetDeviceProcAddr( device, "vkGetDeviceFaultReportsKHR" ) );
        vkGetDeviceFaultDebugInfoKHR = PFN_vkGetDeviceFaultDebugInfoKHR( vkGetDeviceProcAddr( device, "vkGetDeviceFaultDebugInfoKHR" ) );

#if defined( VK_USE_PLATFORM_METAL_EXT )
        //=== VK_EXT_external_memory_metal ===
        vkGetMemoryMetalHandleEXT           = PFN_vkGetMemoryMetalHandleEXT( vkGetDeviceProcAddr( device, "vkGetMemoryMetalHandleEXT" ) );
        vkGetMemoryMetalHandlePropertiesEXT = PFN_vkGetMemoryMetalHandlePropertiesEXT( vkGetDeviceProcAddr( device, "vkGetMemoryMetalHandlePropertiesEXT" ) );
#endif /*VK_USE_PLATFORM_METAL_EXT*/

        //=== VK_ARM_shader_instrumentation ===
        vkCreateShaderInstrumentationARM    = PFN_vkCreateShaderInstrumentationARM( vkGetDeviceProcAddr( device, "vkCreateShaderInstrumentationARM" ) );
        vkDestroyShaderInstrumentationARM   = PFN_vkDestroyShaderInstrumentationARM( vkGetDeviceProcAddr( device, "vkDestroyShaderInstrumentationARM" ) );
        vkCmdBeginShaderInstrumentationARM  = PFN_vkCmdBeginShaderInstrumentationARM( vkGetDeviceProcAddr( device, "vkCmdBeginShaderInstrumentationARM" ) );
        vkCmdEndShaderInstrumentationARM    = PFN_vkCmdEndShaderInstrumentationARM( vkGetDeviceProcAddr( device, "vkCmdEndShaderInstrumentationARM" ) );
        vkGetShaderInstrumentationValuesARM = PFN_vkGetShaderInstrumentationValuesARM( vkGetDeviceProcAddr( device, "vkGetShaderInstrumentationValuesARM" ) );
        vkClearShaderInstrumentationMetricsARM =
          PFN_vkClearShaderInstrumentationMetricsARM( vkGetDeviceProcAddr( device, "vkClearShaderInstrumentationMetricsARM" ) );

        //=== VK_EXT_fragment_density_map_offset ===
        vkCmdEndRendering2EXT = PFN_vkCmdEndRendering2EXT( vkGetDeviceProcAddr( device, "vkCmdEndRendering2EXT" ) );
        if ( !vkCmdEndRendering2KHR )
          vkCmdEndRendering2KHR = vkCmdEndRendering2EXT;

        //=== VK_EXT_custom_resolve ===
        vkCmdBeginCustomResolveEXT = PFN_vkCmdBeginCustomResolveEXT( vkGetDeviceProcAddr( device, "vkCmdBeginCustomResolveEXT" ) );

        //=== VK_KHR_maintenance10 ===
        vkCmdEndRendering2KHR = PFN_vkCmdEndRendering2KHR( vkGetDeviceProcAddr( device, "vkCmdEndRendering2KHR" ) );

        //=== VK_NV_compute_occupancy_priority ===
        vkCmdSetComputeOccupancyPriorityNV = PFN_vkCmdSetComputeOccupancyPriorityNV( vkGetDeviceProcAddr( device, "vkCmdSetComputeOccupancyPriorityNV" ) );

        //=== VK_EXT_primitive_restart_index ===
        vkCmdSetPrimitiveRestartIndexEXT = PFN_vkCmdSetPrimitiveRestartIndexEXT( vkGetDeviceProcAddr( device, "vkCmdSetPrimitiveRestartIndexEXT" ) );
      }

      template <typename DynamicLoader>
      void init( Instance const & instance, Device const & device, DynamicLoader const & dl ) VULKAN_HPP_NOEXCEPT
      {
        PFN_vkGetInstanceProcAddr getInstanceProcAddr = dl.template getProcAddress<PFN_vkGetInstanceProcAddr>( "vkGetInstanceProcAddr" );
        PFN_vkGetDeviceProcAddr   getDeviceProcAddr   = dl.template getProcAddress<PFN_vkGetDeviceProcAddr>( "vkGetDeviceProcAddr" );
        init( static_cast<VkInstance>( instance ), getInstanceProcAddr, static_cast<VkDevice>( device ), device ? getDeviceProcAddr : nullptr );
      }

      template <typename DynamicLoader
#if VULKAN_HPP_ENABLE_DYNAMIC_LOADER_TOOL
                = VULKAN_HPP_NAMESPACE::detail::DynamicLoader
#endif
                >
      void init( Instance const & instance, Device const & device ) VULKAN_HPP_NOEXCEPT
      {
        static DynamicLoader dl;
        init( instance, device, dl );
      }
    };

#if defined( VULKAN_HPP_CXX_MODULE ) && !defined( VULKAN_HPP_DEFAULT_DISPATCHER_HANDLED ) && VULKAN_HPP_DISPATCH_LOADER_DYNAMIC == 1
    VULKAN_HPP_STORAGE_API DispatchLoaderDynamic defaultDispatchLoaderDynamic;
#endif
  }  // namespace detail
}  // namespace VULKAN_HPP_NAMESPACE
#endif
