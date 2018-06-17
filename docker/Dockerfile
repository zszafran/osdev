# name the portage image
FROM gentoo/portage:latest as portage

# image is based on stage3-amd64
FROM gentoo/stage3-amd64:latest

# copy the entire portage volume in
COPY --from=portage /usr/portage /usr/portage

# ZSH
RUN emerge \
  app-shells/zsh \
  app-shells/zsh-completions \
  app-shells/gentoo-zsh-completions

# Oh-My-Zsh
RUN emerge net-misc/curl dev-vcs/git
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

# Crossdev
RUN emerge sys-devel/crossdev
RUN mkdir -p /usr/local/portage/{profiles,metadata}
RUN echo "masters = gentoo" > /usr/local/portage/metadata/layout.conf
RUN echo "osdev" > /usr/local/portage/profiles/osdev
RUN echo "PORTDIR_OVERLAY=\"/usr/local/portage\"" >> /etc/portage/make.conf
RUN crossdev --stage1 --binutils 2.30-r2 --gcc 6.4.0 --target i686-elf
RUN crossdev --stage1 --binutils 2.30-r2 --gcc 6.4.0 --target x86_64-elf
COPY x86_64-elf.make.conf /usr/x86_64-elf/etc/portage/make.conf
COPY i686-elf.make.conf /usr/i686-elf/etc/portage/make.conf

# Grub
RUN emerge sys-boot/grub dev-libs/libisoburn

# Qemu
RUN echo "app-emulation/qemu -* \
  aio \
  xattr \
  bzip2 \
  caps \
  curl \
  ncurses \
  fdt \
  gnutls \
  iscsi \
  modules \
  nfs \
  numa \
  systemtap \
  usb \
  usbredir \
  vhost-net \
  virtfs \
  python_targets_python2_7 \
  qemu_user_targets_i386 \
  qemu_user_targets_x86_64 \
  qemu_softmmu_targets_i386 \
  qemu_softmmu_targets_x86_64" > \
  /etc/portage/package.use/qemu
RUN emerge app-emulation/qemu

# Portage Cleanup
RUN rm -rf /var/tmp/portage

CMD ["/bin/zsh", "-c", "cd /usr/src/osdev; zsh"]