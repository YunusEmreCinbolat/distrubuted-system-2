# distrubuted-system-2

# MPI ve OpenMP Performans Karşılaştırması

## Test Ortamı
- **İşlemci:** 8 Çekirdekli
- **Docker Konteynerleri:** 3 düğüm (1 master, 2 worker)

## Sonuçlar
| Yöntem  | Süre (saniye) |
|---------|--------------|
| MPI     | 2.3          |
| OpenMP  | 1.2          |

### Analiz
- OpenMP, tek bir düğüm içinde çok çekirdek kullanarak daha hızlıdır.
- MPI, çok düğümlü hesaplamalar için uygundur ancak iletişim maliyeti vardır.

# Dağıtık Hesaplama Projesi

Bu proje, MPI ve OpenMP kullanarak dağıtık bir sistemde veri işleme yapmaktadır.

## 🚀 Çalıştırma Adımları
```bash
docker-compose up --build
docker run --rm master_node /app/openmp_program
```
