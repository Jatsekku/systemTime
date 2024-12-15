{
  description = "Development flake for systemTime library";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    logger.url = "github:Jatsekku/logger/main";
  };

  outputs =
    inputs@{ flake-parts, ... }:
    flake-parts.lib.mkFlake { inherit inputs; } {
      systems = [
        "x86_64-linux"
      ];
      perSystem =
        {
          config,
          self',
          inputs',
          pkgs,
          system,
          ...
        }:
        {
          # Set formatter for nix fmt
          formatter = pkgs.nixfmt-rfc-style;

          packages.systemTime = pkgs.callPackage ./package.nix {
            logger = inputs.logger.packages.${system}.default;
          };
          packages.default = config.packages.systemTime;

          devShells.default = config.packages.default;
        };
    };
}
