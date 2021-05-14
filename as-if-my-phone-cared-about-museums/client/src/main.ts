import createSpiral from './createSpiral';
import getCoveredImageData from './getCoveredImageData';

(async () => {
  const assets = 'assets/eyes/06717ea3a03513eab46cf9ac44fda6c7.jpg assets/eyes/165243e4442921c9c8410b94ba386786.jpg assets/eyes/6df691e6cbad7c8cbfbd9fe1d75d578e.png assets/eyes/7408517f06bb70cc1b1d9e72ab0b004a.jpg assets/eyes/916e7368da4d1689e3fa457f0fa48f1e.jpg assets/eyes/9f10401efdd3432698467f84eb6b5251.jpg assets/eyes/acaf78bb6c602103cb778929db3e9a17.jpg assets/eyes/b3d55c4cb2921930c9c7de6a5e3fd6c4.jpg assets/eyes/b41755ca2685b496de93dff3c7bda62a.png assets/eyes/b427223d7b39beee975f67731e03a6c2.jpg assets/eyes/b7a6ad5e7a1acc574a92edb91564392d.jpg assets/eyes/b91b6389da8111e7ff6dd9c8febf1918.jpg assets/eyes/bdc06ea461761cc0905b120cfc86182c.jpg assets/eyes/c0174efbcb4a04c1c9c82d8cf6194aaa.jpg assets/eyes/dc08ed934ed55780d4cf54199471b340.jpg assets/eyes/e0fd9867b536b7dfad0d547902e30c3e.png assets/eyes/ed6ecd16da93051e3a630fe8bff89760.jpg assets/eyes/f35d8979308368d7cd1818780dfc7b54.png assets/eyes/human-eye-macro-up-close.jpg assets/eyes/mme5.webp assets/eyes/mme6.webp assets/eyes/mme7.webp assets/greens/arm1.jpg assets/greens/arm2.jpg assets/greens/DSC_4919.jpg assets/greens/tumblr_46eb2fb2f5d297f1112d81e2ad6f8fb8_ac8e0dec_640.jpg assets/greens/tumblr_504f826105639d6ef4ac441c9fd22ef2_f70a78e5_640.jpg assets/greens/tumblr_7c7ad23bfa3718b5a5d659bc76a6a28b_50a5325f_540.jpg assets/greens/tumblr_8385973497d91f00de98269f8192ccb7_449ea8b7_1280.jpg assets/greens/tumblr_83e199303b96a233dd27e6329529b0c4_148d6e89_1280.jpg assets/greens/tumblr_e672da1f7b43b88ec5b78c978a4cecd8_2bcd9e7f_640.jpg assets/greens/tumblr_m50269eAzs1rusbqgo1_500.jpg assets/greens/tumblr_mvb7ierhIP1rumydco1_500.jpg assets/greens/tumblr_nazj3svHWO1tfeu62o1_640.jpg assets/greens/tumblr_nr7jxwvO3H1ti7ehlo1_1280.jpeg assets/greens/tumblr_nt9edkovYg1rddqy5o1_1280.jpg assets/greens/tumblr_ntz8wtvR1V1r0db55o1_500.jpg assets/greens/tumblr_odwo1cAqve1uajb0zo1_500.jpg assets/greens/tumblr_ox7hg0tV2q1rcutnqo1_500.jpg assets/greens/tumblr_oz09veEpJ61wv0jlqo1_500.jpeg'.split(' ').map((s) => `/${s}`);
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
    const dist = +(await fetch('http://localhost:8081').then((resp) => resp.text()));
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
