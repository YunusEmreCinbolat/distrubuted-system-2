FROM ubuntu:latest

# Temel bağımlılıkları yükle
RUN apt-get update && apt-get install -y \
    mpich \
    libomp-dev \
    build-essential \
    openssh-client \
    openssh-server

# SSH servisini çalıştırmak için gerekli ayarları yap
RUN mkdir -p /var/run/sshd && \
    echo 'root:root' | chpasswd && \
    sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config && \
    sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config && \
    sed -i 's/PasswordAuthentication no/PasswordAuthentication yes/' /etc/ssh/sshd_config

# SSH bağlantısı için doğrulama iptalini etkinleştir (Host key verification sorunlarını çözer)
RUN mkdir -p /root/.ssh && \
    touch /root/.ssh/known_hosts && \
    echo "StrictHostKeyChecking no" >> /etc/ssh/ssh_config

# SSH için root kullanıcısına yetki ver ve otomatik şifreleme anahtarları oluştur
RUN ssh-keygen -A && \
    mkdir -p /root/.ssh && \
    ssh-keygen -t rsa -f /root/.ssh/id_rsa -q -N "" && \
    cp /root/.ssh/id_rsa.pub /root/.ssh/authorized_keys && \
    chmod 600 /root/.ssh/authorized_keys && \
    chmod 700 /root/.ssh

# SSH bağlantısını master node'un diğer worker node'lara erişebilmesi için yapılandır
RUN echo "Host worker1\n  IdentityFile /root/.ssh/id_rsa\n  StrictHostKeyChecking no" >> /root/.ssh/config && \
    echo "Host worker2\n  IdentityFile /root/.ssh/id_rsa\n  StrictHostKeyChecking no" >> /root/.ssh/config

# Çalışma dizinini ayarla ve /app klasörünü oluştur
WORKDIR /app
RUN mkdir -p /app/src  # /app/src klasörünün varlığını garanti et

# Kaynak kodlarını kopyala
COPY src /app/src

# MPI ve OpenMP için derleme komutları
RUN mpicc -o /app/mpi_program /app/src/mpi_program.c && \
    chmod +x /app/mpi_program  # Çalıştırılabilir izni ekle

RUN gcc -fopenmp -o /app/openmp_program /app/src/openmp_program.c && \
    chmod +x /app/openmp_program  # Çalıştırılabilir izni ekle

# SSH servisinin çalışmasını sağla ve MPI'yi başlat
CMD ["/bin/bash", "-c", "/usr/sbin/sshd -D"]
