#include <iostream>
#include <immintrin.h>

void addVectorsSIMD(const float* a, const float* b, float* result, size_t size)
{
    for (size_t i = 0; i < size; i += 8) 
    {
        __m256 vecA = _mm256_loadu_ps(&a[i]);
        __m256 vecB = _mm256_loadu_ps(&b[i]);
        __m256 vecR = _mm256_add_ps(vecA, vecB);
        _mm256_storeu_ps(&result[i], vecR);
    }
}

void multiplyVectorsSIMD(const float* a, const float* b, float* result, size_t size)
{
    for (size_t i = 0; i < size; i += 8) 
    {
        __m256 vecA = _mm256_loadu_ps(&a[i]);
        __m256 vecB = _mm256_loadu_ps(&b[i]);
        __m256 vecR = _mm256_mul_ps(vecA, vecB);
        _mm256_storeu_ps(&result[i], vecR);
    }
}

void horizantalAddSIMD(const float* a, const float* b, float* result, size_t size)
{
    for (size_t i = 0; i < size; i += 8) 
    {
        __m256 vecA = _mm256_loadu_ps(&a[i]);
        __m256 vecB = _mm256_loadu_ps(&b[i]);
        __m256 vecR = _mm256_add_ps(vecA, vecB);
        __m256 temp = _mm256_hadd_ps(vecR, vecR);
        temp = _mm256_hadd_ps(temp, temp);
        _mm256_storeu_ps(&result[i], temp);
    }
}

int main() 
{
    constexpr size_t size = 16;

    alignas(32) float fa[size] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
                                 9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f};
    alignas(32) float fb[size] = {16.0f, 15.0f, 14.0f, 13.0f, 12.0f, 11.0f, 10.0f, 9.0f,
                                 8.0f, 7.0f, 6.0f, 5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    alignas(32) float fresult[size] = {0.0f};

    __declspec(align(16)) int ia[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    __declspec(align(16)) int ib[size] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    __declspec(align(16)) int iresult[size] = {0};

    // addVectorsSIMD(fa, fb, fresult, size);
    multiplyVectorsSIMD(fa, fb, fresult, size);
    addVectorsSIMD(reinterpret_cast<float*>(ia), reinterpret_cast<float*>(ib), reinterpret_cast<float*>(iresult), size);

    for (size_t i = 0; i < size; ++i) 
        std::cout << fresult[i] << " ";

    std::cout<<std::endl;

    for(size_t i = 0; i < size; ++i) 
        std::cout << iresult[i] << " ";
    
    std::cout << std::endl;

    return 0;
}