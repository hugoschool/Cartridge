{
  inputs = {
    utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, utils }: utils.lib.eachDefaultSystem (system:
    let
      pkgs = nixpkgs.legacyPackages.${system};
    in
    {
      devShell = pkgs.mkShell {
        buildInputs = with pkgs; [
          gcc-arm-embedded
          newlib
        ];

        shellHook = ''
          export CC=${pkgs.gcc-arm-embedded}/bin/arm-none-eabi-gcc
        '';
      };
    }
  );
}
