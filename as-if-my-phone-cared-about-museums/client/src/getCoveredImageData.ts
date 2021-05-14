export default async (src: string, width: number, height: number): Promise<ImageData> => {
  const image = new Image();
  image.src = src;
  await new Promise((r) => { image.onload = r; });

  const srcRatio = image.width / image.height;
  const dstRatio = width / height;
  const srcWidth = srcRatio < dstRatio
    ? image.width
    : image.width * (dstRatio / srcRatio);
  const srcHeight = srcRatio < dstRatio
    ? image.height * (srcRatio / dstRatio)
    : image.height;

  const canvas = document.createElement('canvas');
  canvas.width = width;
  canvas.height = height;
  const ctx = canvas.getContext('2d');
  ctx.drawImage(
    image,
    (image.width - srcWidth) / 2,
    (image.height - srcHeight) / 2,
    srcWidth,
    srcHeight,
    0, 0, width, height,
  );

  return ctx.getImageData(0, 0, width, height);
};
