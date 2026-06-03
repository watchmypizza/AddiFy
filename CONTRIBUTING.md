# Contributing to AddiFy

Thank you for your interest in contributing to AddiFy.

This project is maintenance-focused and aims to remain minimal, stable, and predictable. Contributions that align with this philosophy are welcome.

---

## Project Scope

AddiFy is a C++ application designed to automate playlist population using Spotify web endpoints.

The project is considered feature-complete. Contributions should focus on:

- Bug fixes
- Compatibility updates (Spotify endpoint changes)
- Build/system improvements
- Documentation improvements
- Performance or reliability refinements

Feature expansion outside of the existing scope is generally not accepted.

---

## Code Philosophy

Please keep the following principles in mind:

- Keep the codebase minimal and readable
- Avoid unnecessary abstractions
- Prefer direct solutions over framework-style design
- Do not introduce external dependencies without strong justification
- Maintain deterministic behavior where possible

---

## Requirements

Before contributing, ensure you have:

- A C++20 compatible compiler (g++ or clang++)
- libcurl installed
- yaml-cpp installed
- A Linux-based development environment (recommended)

---

## Build Instructions

Clone the repository:

```sh
git clone https://github.com/watchmypizza/AddiFy.git
cd AddiFy
```

Build using Makefile

```sh
make
```

Or build manually
```sh
g++ Classes/*.cpp -o AddiFy -lcurl -lyaml-cpp -I/usr/include -std=c++20
```

## Development Workflow

1. Fork the Repository
2. Create a feature branch
```sh
git checkout -b fix/your-fix-name
```
3. Make your changes
4. Ensure the project builds successfully
5. Test manually using a valid `config.yaml`
6. Commit your changes with clear messages
7. Push your fork
8. Open a pull request

## Commit Guidelines

Keep commits small and descriptive.

Good examples:

* fix: handle expired authorization token gracefully
* refactor: simplify YAML config parsing
* fix: correct playlist ID parsing edge case
* docs: update authentication instructions

Avoid vague commits like:

* fix stuff
* updates
* changes

## Pull Request Guidelines

When opening a pull request:

* Clearly describe what was changed and why
* Reference any related issues if applicable
* Include testing notes if behavior changes
* Ensure no unrelated refactoring is included

Pull requests that break existing behavior without justification will not be accepted.

## Security & API Behavior

This project interacts with Spotify web endpoints that are not officially intended for public automation.

When contributing:

* Do not introduce aggressive request patterns
* Avoid changes that increase risk of rate limiting
* Do not attempt to bypass authentication restrictions
* Respect API response limits and error handling

## Testing

There is no automated test suite at this time.

All changes should be manually verified using:

* A valid `config.yaml`
* A test playlist (recommended, not your main account)
* A small artist dataset before large runs

## Documentation

If you modify behavior, update the README accordingly.

Documentation clarity is considered part of the contribution.

## Final Notes

This project prioritizes stability over expansion.

If your contribution makes the code simpler, safer, or more reliable, it is likely to be accepted.

If it increases complexity without clear benefit, it likely will not.

Thank you for contributing to AddiFy.