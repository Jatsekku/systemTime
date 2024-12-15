{
  meson,
  ninja,
  lib,
  logger,
  stdenv,
  nixfmt-rfc-style,
}:

stdenv.mkDerivation {
  pname = "systemTime";
  version = "0.0.1";

  src = ./.;

  nativeBuildInputs = [
    meson
    ninja
    nixfmt-rfc-style
  ];

  buildInputs = [
    logger
  ];
}
