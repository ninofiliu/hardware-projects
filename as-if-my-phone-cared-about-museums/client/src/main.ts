import createSpiral from './createSpiral';
import getCoveredImageData from './getCoveredImageData';
import assets from './assets';

(async () => {
  const eyes = assets.filter((s) => s.startsWith('/assets/eyes'));
  const greens = assets.filter((s) => s.startsWith('/assets/greens'));
  console.log({ eyes, greens });

  const randomArrayPick = <T>(arr: T[]): T => arr[Math.floor(Math.random() * arr.length)];
  const width = window.innerWidth;
  const height = window.innerHeight;
  const canvas = document.querySelector('canvas');
  canvas.width = width;
  canvas.height = height;
  const ctx = canvas.getContext('2d');

  const imageLoop = async () => {
    // const dist = +(await fetch('http://localhost:8081').then((resp) => resp.text()));
    const theme: 'eyes' | 'greens' = 'greens';
    const mono = Math.random() < 0.8;
    const asset = randomArrayPick({ eyes, greens }[theme]);
    const imageData = await getCoveredImageData(asset, width, height);
    const spiral = createSpiral({
      ctx,
      width,
      height,
      imageData,
      colorChannel: 0,
      stopAt: { eyes: 0.4, greens: 0.5 }[theme],
      kind: 'looped',
      divider: { eyes: 10, greens: 10 }[theme],
      multiplier: { eyes: 3, greens: 5 }[theme],
    });
    const updateLoop = async () => {
      for (let i = 0; i < 1000; i++) {
        const index = 4 * (width * spiral.y + spiral.x);
        const { r, g, b } = {
          eyes: {
            r: imageData.data[index],
            g: mono ? 0 : imageData.data[index + 1],
            b: mono ? 0 : imageData.data[index + 2],
          },
          greens: {
            r: imageData.data[index],
            g: imageData.data[index + 1],
            b: imageData.data[index + 2],
          },
        }[theme];
        ctx.fillStyle = `rgb(${r}, ${g}, ${b})`;
        ctx.fillRect(spiral.x, spiral.y, 1, 1);
        spiral.move();
        if (spiral.done) {
          imageLoop();
          return;
        }
        await new Promise<void>((resolve) => resolve());
      }
      requestAnimationFrame(updateLoop);
    };
    updateLoop();
  };
  imageLoop();
})();
