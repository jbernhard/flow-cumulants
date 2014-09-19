#include<algorithm>
#include<cmath>
#include<complex>
#include<iomanip>
#include<iostream>
#include<map>
#include<string>
#include<vector>


const double eta_max = 2.0;
const double pT_width = 0.1;
const unsigned Qn_max = 8;


int main() {
  // massive speedup reading stdin
  // https://stackoverflow.com/q/9371238
  std::cin.sync_with_stdio(false);
  std::cout << std::fixed;

  std::string line;
  const double twice_eta_max = 2.*eta_max;
  std::map<size_t, std::vector<double>> particles;

  while (std::cin) {
    std::getline(std::cin, line);
    if (line.size() < 400) {
      if (!particles.empty()) {
        for (const auto& bin : particles) {
          auto index = bin.first;
          auto phi_vector = bin.second;
          std::cout << std::setprecision(2)
              << index*pT_width << ' '
              << (index+1)*pT_width << ' '
              << std::setw(5) << phi_vector.size();

          for (unsigned n = 2; n <= Qn_max; ++n) {
            std::complex<double> Qn;
            for (const auto& p : phi_vector) {
              Qn += std::exp(std::complex<double>(0., n*p));
            }
            std::cout << std::setprecision(8)
                << std::setw(13) << Qn.real()
                << std::setw(13) << Qn.imag();
          }
          std::cout << '\n';
        }
        std::cout << '\n';
        particles.clear();
      }
      continue;
    }


    auto charge = std::stoi(line.substr(225, 2));
    if (charge == 0)
      continue;

    // make Fortran doubles readable
    std::replace(line.begin(), line.end(), 'D', 'E');

    auto px = std::stod(line.substr(121, 23));
    auto py = std::stod(line.substr(145, 23));
    auto pz = std::stod(line.substr(169, 23));

    auto pmag = std::sqrt(px*px + py*py + pz*pz);
    auto twice_eta = std::log((pmag+pz)/(pmag-pz));

    if (twice_eta > twice_eta_max)
      continue;

    auto pT = std::hypot(px, py);
    auto phi = std::atan2(py, px);

    auto pT_index = static_cast<size_t>(pT/pT_width);

    particles[pT_index].push_back(phi);
  }

  return 0;
}
