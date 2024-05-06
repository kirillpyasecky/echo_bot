## Echo bot

### Run
- Creat config file with your bot token, example down below:
```config.json
{
    "BOT_TOKEN": "<your_token>"
}
```
- Build project:
```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j8
./echo_bot
```