#include <iostream>
#include <vector>
#include <complex>
#include <cmath>

class FFT {
public:
    // Initializing the main function
    // Perform the Cooley-Tukey Radix-2 FFT on a vector of complex numbers.
    void fft(std::vector<std::complex<double>>& data, bool inverse = false) {
        int n = data.size();
        if (n <= 1) {
            return;
        }

        // Separate even and odd elements
        std::vector<std::complex<double>> even;
        std::vector<std::complex<double>> odd;
        for (int i = 0; i < n; i += 2) {
            even.push_back(data[i]);
            odd.push_back(data[i + 1]);
        }

        // Recursively compute FFT for even and odd parts
        // This recursively applys the void function
        fft(even, inverse);
        fft(odd, inverse);

        // Combine the results
        double angle = 2 * M_PI / n * (inverse ? -1 : 1);
        std::complex<double> w(1);
        std::complex<double> wn(std::cos(angle), std::sin(angle));
        for (int k = 0; k < n / 2; ++k) {
            std::complex<double> t = w * odd[k];
            data[k] = even[k] + t;
            data[k + n / 2] = even[k] - t;
            w *= wn;
        }
        // this is also important to notice
        if (inverse) {
            for (int i = 0; i < n; ++i) {
                data[i] /= n;
            }
        }
    }
};

int main() {
    FFT fft;

    // Create a vector of complex numbers to be transformed.
    std::vector<std::complex<double>> data = {
        std::complex<double>(1.0, 0.0),
        std::complex<double>(2.0, 0.0),
        std::complex<double>(3.0, 0.0),
        std::complex<double>(4.0, 0.0)
    };

    // Perform the FFT on the data vector.
    fft.fft(data);

    // Print the results.
    for (const auto& complexNum : data) {
        std::cout << "Real: " << complexNum.real() << ", Imaginary: " << complexNum.imag() << std::endl;
    }

    return 0;
}
